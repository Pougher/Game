#include "shader.hpp"

using namespace rac;

static inline std::string load_file(const std::string &filename) {
    std::ifstream f(filename);
    std::stringstream buffer;

    if (!f.is_open()) {
        rlog::error("Error opening file '" + filename + "': File not found.");
    }

    buffer << f.rdbuf();

    f.close();
    return buffer.str();
}

Shader::Shader(const std::string &vs, const std::string &fs, bool is_file) {
    this->compilation_failure = false;
    if (is_file) {
        this->compile_shader_from_strings(load_file(vs), load_file(fs));
        if (!this->compilation_failure) {
            rlog::info("Successfully compiled shader '" + fs + "'");
            rlog::info("Successfully compiled shader '" + vs + "'");
        } else {
            rlog::info("Failed to compile shaders '" + fs + "' and '"
                + vs + "'");
        }
    } else {
        this->compile_shader_from_strings(vs, fs);
    }
}

Shader::Shader() {
    this->compilation_failure = false;
}

void Shader::compile_shader_from_strings(
    const std::string &vs,
    const std::string &fs) {
    const char *vertex_source = vs.c_str();
    const char *fragment_source = fs.c_str();

    u32 vertex_shader, fragment_shader;

    // compile the vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);

    // compile the fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);

#ifndef NDEBUG
    this->get_shader_compile_messages(vertex_shader, GL_COMPILE_STATUS);
    this->get_shader_compile_messages(fragment_shader, GL_COMPILE_STATUS);
#endif

    this->id = glCreateProgram();
    glAttachShader(this->id, vertex_shader);
    glAttachShader(this->id, fragment_shader);
    glLinkProgram(this->id);

#ifndef NDEBUG
    this->get_shader_compile_messages(this->id, GL_LINK_STATUS);
#endif
}

void Shader::get_shader_compile_messages(u32 shader, GLenum type) {
    int success;
    char info[512];

    glGetShaderiv(shader, type, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info);
        rlog::error("Issue compiling shader: " + std::string(info));

        this->compilation_failure = true;
    }
}

void Shader::use() {
    glUseProgram(this->id);
}

void Shader::destroy() {
    this->compilation_failure = false;
    glDeleteProgram(this->id);
}
