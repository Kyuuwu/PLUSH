#include "Window/Window.hpp"
#include "GraphicsLayer/GraphicsLayer.hpp"
#include "GraphicsLayer/ManagedGraphicsLayer.hpp"
#include "Shader/ManagedShader.hpp"
#include "Window/WindowSpec.hpp"
#include "Window/WindowIdentifier.hpp"
#include "PlushGraphicsException.hpp"
#include "OpenGL.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <set>
#include "../include/GlobalGraphicsState.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glfwMakeContextCurrent(window); // temporarily switch to window pointer off-books
    glViewport(0,0,width, height);
    PlushGraphics::GlobalGraphicsState::switchContextToWindow(PlushGraphics::GlobalGraphicsState::getActiveWindowIdentifier()); 
    // then switch back to active window
}

namespace PlushGraphics {
    Window::Window(WindowSpec windowbuilder):
    identifier(windowbuilder.getWindowName()),
    settings(windowbuilder.settings),
    resolver(windowbuilder.resolver->duplicateSelf())
    {
        windowPointer = glfwCreateWindow(windowbuilder.getWindowWidth(), windowbuilder.getWindowHeight(), windowbuilder.getWindowName().c_str(), NULL, GlobalGraphicsState::getRootContext());

        if(windowPointer == NULL){
            std::cout << "Failed to create GLFW window" << std::endl;
            throw(PlushGraphicsException::FAILED_TO_CREATE_WINDOW);
        }

        glfwMakeContextCurrent(windowPointer); // off books context switch

        if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
            std::cout << "Failed to initialize GLAD" << std::endl;
            throw 2;
        }

        glfwSwapInterval(1); // Use vysnc, for now
        // Interestingly Vsync does not cause problems for multiwindow, ie 60 fps doesnt become 30 fps, waiting for one screen update per window frame
        glfwSetFramebufferSizeCallback(windowPointer, framebuffer_size_callback);

        glViewport(0,0,windowbuilder.getWindowWidth(), windowbuilder.getWindowHeight());
        PlushGraphics::GlobalGraphicsState::switchContextToWindow(PlushGraphics::GlobalGraphicsState::getActiveWindowIdentifier()); 
        // then switch back to active window
    };

    Window::~Window()
    {
        glfwDestroyWindow(windowPointer); // destroy window
    }

    void Window::_performDrawCycle() {
        PlushGraphics::GlobalGraphicsState::switchContextToWindow(getIdentifier());

        glClearColor(settings.clearColor.r, settings.clearColor.g, settings.clearColor.b, settings.clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT);

        std::set<ManagedShader> necessaryShaders;

        for(ManagedGraphicsLayer layer : graphicsLayers){
            std::set<ManagedShader> layerShaders = layer.getNecessaryShaders();

            necessaryShaders.insert(layerShaders.begin(), layerShaders.end());
        }

        for(ManagedShader shader : necessaryShaders){
            shader.clearWindowLevelUniforms();
            shader.prepareForWindowUniforms();
            shader.acceptUniformResolver(resolver);
        }

        for(ManagedGraphicsLayer layer : graphicsLayers){
            layer.performDrawCycle();
        }

        _swapBuffers();
    }

    void Window::_addGraphicsLayer(ManagedGraphicsLayer layer) {
        graphicsLayers.push_back(layer);
    }
}