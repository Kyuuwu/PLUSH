#include "OpenGL.h"
#include "PlushGraphicsOpenGL.hpp"
#include "../include/Window/WindowSpec.hpp"
#include <iostream>

namespace PlushGraphics {
    void GlobalGraphicsState::initializeOpenGL(){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        PlushGraphics::WindowSpec builder;

        activeWindowIdentifier = windowRegistry.loadItem(builder);
        PlushGraphics::ManagedWindow window = windowRegistry.getItem(activeWindowIdentifier);
        rootContext = window->windowPointer;
    }

    void GlobalGraphicsState::terminateOpenGL() {
        glfwTerminate();
    }
}