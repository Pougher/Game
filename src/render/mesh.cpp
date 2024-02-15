#include "mesh.hpp"

using namespace rac;

Mesh::Mesh() {
    // set the last attribute to zero so we dont get undefined indexes into
    // memory
    this->last_attr = 0;

    // set the number of triangles to be drawn to zero
    this->indices = 0;
}

template<typename T>
void Mesh::push(const std::vector<T> &data, size_t indices) {
    char *end;
    size_t old_size = this->vertices.size();
    bool empty = this->vertices.empty();

    this->vertices.resize(this->vertices.size() + data.size() * sizeof(T));
    if (empty) {
        end = &(this->vertices[0]);
    } else {
        end = &(this->vertices[0]) + old_size;
    }

    std::memcpy(
        end,
        data.data(),
        data.size() * sizeof(T)
    );

    this->indices += indices;
}

void Mesh::attribute(const MeshAttribute &attribute) {
    this->attributes.push_back(attribute);
    this->last_attr += attribute.size;
}

void Mesh::render() const {
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, this->indices);
}

void Mesh::build() {
    // delete the old VAO and VBO
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);

    // generate the VAO
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    // generate the VBO
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(
        GL_ARRAY_BUFFER,
        this->vertices.size(),
        this->vertices.data(),
        GL_STATIC_DRAW
    );

    size_t attribute = 0;
    for (const MeshAttribute &attr : this->attributes) {
        glVertexAttribIPointer(
            attribute,
            attr.length,
            attr.type,
            //GL_FALSE,
            this->last_attr,
            attr.index
        );
        glEnableVertexAttribArray(attribute);

        attribute++;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void *Mesh::last() const {
    return (void*)this->last_attr;
}

void Mesh::destroy() {
    this->last_attr = 0;
    this->indices = 0;

    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
}

template void Mesh::push<float>(const std::vector<float>&, size_t);
template void Mesh::push<u32>(const std::vector<u32>&, size_t);
