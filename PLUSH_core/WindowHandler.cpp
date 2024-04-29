#include "PLUSH_core_includes.h"
#include "OPENGL_management_includes.h"
#include <iostream>
#include "Helpers.h"

namespace PLUSH {
    WindowHandler::WindowHandler(std::string name){
        window = std::shared_ptr<OPENGL_management::Window>(new OPENGL_management::Window(name));

        window->Create();
    }

    bool WindowHandler::ShouldClose(){
        return window->ShouldClose();
    }

    float WindowHandler::getAspectRatio(){
        return window->getAspectRatio();
    }

    float WindowHandler::getInverseAspectRatio(){
        return window->getInverseAspectRatio();
    }

    void WindowHandler::addDrawableLayer(std::shared_ptr<DrawableLayer> newLayer){
        for (std::shared_ptr<DrawableLayer> layer : layers){
            if (layer->getName() == newLayer->getName()){
                std::cout << "Error: Didn't add layer, because layer with matching name was found in layer list." << std::endl;
                return;
            }
        }
        layers.push_back(newLayer);
    }
    
    void WindowHandler::addStandardLayer(std::shared_ptr<Standard_Layer> newLayer)
    {
        for (std::shared_ptr<Standard_Layer> layer : standard_layers){
            if (layer->getName() == newLayer->getName()){
                std::cout << "Error: Didn't add layer, because layer with matching name was found in layer list." << std::endl;
                return;
            }
        }
        standard_layers.push_back(newLayer);
    }
    
    std::weak_ptr<Standard_Layer> WindowHandler::getStandardLayer(std::string name)
    {
        for(std::shared_ptr<Standard_Layer> layer: standard_layers){
            if (layer->getName() == name){
                return layer;
            }
        }
        throw(LAYER_NOT_FOUND);
    }

    void WindowHandler::draw(){
        OPENGL_management::clearWindow(window.get(), clearColor[0], clearColor[1], clearColor[2]);

        std::vector<OPENGL_management::ShaderUniform> window_uniforms = window->getWindowUniforms();

        // for(std::shared_ptr<DrawableLayer> layer : layers){
        //     layer->draw(window_uniforms);
        // }

        for(std::shared_ptr<Standard_Layer> layer : standard_layers){
            layer->draw(window_uniforms);
        }

        window->swapBuffers();
    }

    void WindowHandler::setClearColor(float r, float g, float b){
        clearColor[0] = r;
        clearColor[1] = g;
        clearColor[2] = b;
    }

    void WindowHandler::setDepthTest(bool depthTest){
        if (depthTest){
            OPENGL_management::enableDepthTest(window.get());
        } else{
            OPENGL_management::disableDepthTest(window.get());
        }
    }

    PLUSH_helpers::KeyboardStatus* WindowHandler::getKeyboardStatusPointer(){
        return window->getKeyboardStatusPointer();
    }

    PLUSH_helpers::MouseStatus* WindowHandler::getMouseStatusPointer(){
        return window->getMouseStatusPointer();
    }

    void WindowHandler::Close(){
        window->Close();
    }
    
    double WindowHandler::getMouseX(){
        return window->getMouseX();
    }
    
    double WindowHandler::getMouseY(){
        return window->getMouseY();
    }

    double WindowHandler::getMouseYAspectScaled(){
        return window->getMouseYAspectScaled();
    }
}