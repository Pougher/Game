#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "../common/types.hpp"

/*
 * Thanks Creo for helping me get through this one :/
 */

namespace rac {

struct Mesh {
    using byte = char;

    // structure to hold mesh attributes that are then applied to the mesh
    // when it is constructed
    struct MeshAttribute {
        // the type of the mesh attribute
        GLenum type;

        // the mesh attributes' length in elements
        size_t length;

        // the mesh attributes' size in bytes
        size_t size;

        // the index into the mesh vector that the attribute sits at
        void *index;
    };

    // vertices stored as bytes such that any type may be appended to them
    std::vector<byte> vertices;

    // the attributes that the vertices contain
    std::vector<MeshAttribute> attributes;

    // the last pointer length into the mesh, increases every time a new
    // mesh attribute is added
    size_t last_attr;

    // number of triangles that OpenGL needs to draw
    size_t indices;

    // vertex attribute object
    u32 vao;

    // vertex buffer object
    u32 vbo;

    // initializes attributes of the mesh
    Mesh();

    // pushes the vector of data onto the top of the vertices vector, resizing
    // the vertices data vector as required. Also increments the indices value
    // by the integer supplied, signifying the number of additional triangles
    // that this push requires to be drawn
    template<typename T>
    void push(const std::vector<T>&, size_t);

    // adds an attribute to the end of the attributes vector
    void attribute(const MeshAttribute&);

    // constructs the mesh and provides a VAO and VBO for OpenGL to bind to
    void build();

    // renders the mesh using OpenGL draw calls
    void render() const;

    // gets the last attribute index as void*
    void *last() const;

    // destroys all data held by the mesh
    void destroy();
};

}
