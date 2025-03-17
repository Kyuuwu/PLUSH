#include "../include/Window/Window.hpp"
#include "../include/Window/WindowSpec.hpp"
#include "../include/Window/WindowIdentifier.hpp"
#include "PlushGraphicsException.hpp"
#include "OpenGL.h"
#include <iostream>
#include "PlushGraphicsOpenGL.hpp"

namespace PlushGraphics {
    Window::Window(WindowSpec windowbuilder):
    identifier(windowbuilder.getWindowName())
    {
        windowPointer = glfwCreateWindow(windowbuilder.getWindowWidth(), windowbuilder.getWindowHeight(), windowbuilder.getWindowName().c_str(), NULL, GlobalGraphicsState::getRootContext());

        if(windowPointer == NULL){
            std::cout << "Failed to create GLFW window" << std::endl;
            throw(PlushGraphicsException::FAILED_TO_CREATE_WINDOW);
        }

        glfwMakeContextCurrent(windowPointer); // for now

        if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
            std::cout << "Failed to initialize GLAD" << std::endl;
            throw 2;
        }

        glViewport(0,0,windowbuilder.getWindowWidth(), windowbuilder.getWindowHeight());
    };

    Window::~Window()
    {
        glfwDestroyWindow(windowPointer); // destroy window
    }
}