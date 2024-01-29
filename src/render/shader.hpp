#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
    void use();

    // destroys the program within the struct
    void destroy();
};

}
