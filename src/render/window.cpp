#include "window.hpp"

using namespace rac;

Window::Window() { /* do nothing */ }

Window::Window(const std::string &name, u32 w, u32 h) {
    this->create(name, w, h);
}

void Window::create(const std::string &name, u32 w, u32 h) {
    this->init();

    this->window = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
    this->width = w;
    this->height = h;

    if (this->window == NULL) {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();

        std::exit(-1);
    }
    glfwMakeContextCurrent(this->window);

    this->init_glew();

    glViewport(0, 0, w, h);
}

void Window::init() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void Window::init_glew() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();

        std::exit(-1);
    }
}

void Window::update() {
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

void Window::cleanup() {
    glfwTerminate();
}
