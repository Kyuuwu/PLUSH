#include "OpenGL.h"
#include "../include/GlobalGraphicsState.hpp"
#include "UniformResolver.hpp"
#include "Window/WindowSpec.hpp"
#include <iostream>
#include "UniformResolvers/NoOpResolver.hpp"

namespace PlushGraphics {
    void GlobalGraphicsState::initializeOpenGL(){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        WindowSettings initialWindowSettings;
        initialWindowSettings.windowName = "first Window";
        PlushGraphics::WindowSpec builder(UniformResolvers::NoOpResolver(), initialWindowSettings);

        activeWindowId = windowRegistry.loadItem(builder);
        PlushGraphics::ManagedWindow window = windowRegistry.getItem(*activeWindowId);
        rootContext = window->windowPointer;
    }

    void GlobalGraphicsState::terminateOpenGL() {
        glfwTerminate();
    }
}