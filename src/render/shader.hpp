#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>

#include "../common/types.hpp"
#include "../common/log.hpp"

namespace rac {

struct Shader {
    // the ID of the shader
    unsigned int id;

    // variable that is true if a compilation failure has occurred. This value
    // is only updated in debug builds
    bool compilation_failure;

    // loads shaders from either a file or directly from the std::string
    // depending on wether or not is_file (bool) is true or false, with true
    // denoting a direct shader load. The shaders are then compiled and linked
    Shader(const std::string&, const std::string&, bool);

    // does nothing, so the shader may be populated with data later on
    Shader();

    // compiles a shader from two strings - the fragment shader and the vertex
    // shader
    void compile_shader_from_strings(const std::string&, const std::string&);

    // gets the compile messages for shaders
    void get_shader_compile_messages(u32, GLenum);

    // attaches the shader to OpenGL
    void use() const;

    // destroys the program within the struct
    void destroy();

    // setters for various information that we may need to pass to a shader
    // Each function is prefixed by 'set' and is followed by the type that they
    // pass to the shader, so set_mat4 would set a mat4 (4x4 matrix) in the
    // shader
    void set_bool(const std::string&, bool) const;
    void set_int(const std::string&, int) const;
    void set_float(const std::string&, float) const;
    void set_vec2(const std::string&, const glm::vec2&) const;
    void set_vec3(const std::string&, const glm::vec3&) const;
    void set_vec4(const std::string&, const glm::vec4&) const;
    void set_mat2(const std::string&, const glm::mat2&) const;
    void set_mat3(const std::string&, const glm::mat3&) const;
    void set_mat4(const std::string&, const glm::mat4&) const;
};

}
