#include "OpenGL.h"
#include "PlushGraphicsOpenGL.hpp"

namespace PlushGraphics {
    void OpenGL::initializeOpenGL(){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

    void OpenGL::terminateOpenGL() {
        glfwTerminate();
    }
}