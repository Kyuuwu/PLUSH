#include "OPENGL_includes.h"
#include "OPENGL_management_includes.h"
#include "Helpers.h"

#include <string>
#include <functional>
#include <iostream>

namespace OPENGL_management{
    Window::Window(std::string title){
        setTitle(title);
        keyboardstatus = PLUSH_helpers::getFreshKeyboard();
    }

    float Window::getAspectRatio(){
        return ((float) window_width) / ((float) window_height);
    }

    float Window::getInverseAspectRatio(){
        return ((float) window_height) / ((float) window_width);
    }

    void Window::Create(){
        if (WindowActive()){
            throw(WINDOW_NOT_CLOSED);
        }

        window = createWindow(window_width, window_height, window_title.c_str());
        glViewport(0,0,window_width, window_height);

        glfwSetWindowUserPointer(window, this);

        auto func = [](GLFWwindow* w, int width, int height){
            static_cast<Window*>(glfwGetWindowUserPointer(w))->framebuffer_size_callback(w, width, height);
        };

        glfwSetFramebufferSizeCallback(window, func);

        auto func_key = [](GLFWwindow* window, int key, int scancode, int action, int mods){
            static_cast<Window*>(glfwGetWindowUserPointer(window))->key_callback(window, key, scancode, action, mods);
        };

        glfwSetKeyCallback(window, func_key);

        auto func_mouse = [](GLFWwindow* window, double x_pos, double y_pos){
            static_cast<Window*>(glfwGetWindowUserPointer(window))->mouse_pos_callback(window, x_pos, y_pos);
        };

        glfwSetCursorPosCallback(window, func_mouse);

        auto func_mouse_click = [](GLFWwindow* window, int button, int action, int mods){
            static_cast<Window*>(glfwGetWindowUserPointer(window))->mouse_button_callback(window, button, action, mods);
        };
        
        glfwSetMouseButtonCallback(window, func_mouse_click);

        windowActive = true;
    }

    void Window::Close(){
        glfwSetWindowShouldClose(window, true);
    }

    void Window::Destroy(){
        if(!WindowActive()){
            throw(WINDOW_NOT_ACTIVE);
        }

        glfwDestroyWindow(window);
        windowActive = false;
    }

    GLFWwindow* Window::getWindowPointer(){
        return window;
    }

    bool Window::WindowActive(){
        return windowActive;
    }

    bool Window::ShouldClose(){
        return glfwWindowShouldClose(window);
    }

    void Window::setTitle(std::string title){
        window_title = title;

        if(WindowActive()){
            glfwSetWindowTitle(window, title.c_str());
        }
    }

    Dimensions Window::getDimensions(){
        Dimensions dims;
        dims.width = window_width;
        dims.height = window_height;
        return dims;
    }

    void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height){
        window_height = height;
        window_width = width;

        glfwMakeContextCurrent(window);
        glViewport(0,0,width, height);

        window_uniforms_up_to_date = false;
    }

    void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
        // std::cout << "Key pressed" << std::endl;

        switch(action){
            case GLFW_PRESS:{
                keyboardstatus.keystatus[PLUSH_helpers::getKeyFromOpenGL_Key(key)] = PLUSH_helpers::JUST_PRESSED;
                break;
            }
            case GLFW_RELEASE:{
                keyboardstatus.keystatus[PLUSH_helpers::getKeyFromOpenGL_Key(key)] = PLUSH_helpers::JUST_RELEASED;
                break;
            }
            default:
                break;
        }
    }

    void Window::mouse_pos_callback(GLFWwindow *window, double x_pos, double y_pos){
        mouseX = x_pos;
        mouseY = y_pos;
    }

    void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
        if(button == GLFW_MOUSE_BUTTON_LEFT){
            if(action == GLFW_PRESS){
                mousestatus.LEFT_MOUSE_PRESSED = true;
            }else{
                mousestatus.LEFT_MOUSE_PRESSED = false;
            }
        }
        if(button == GLFW_MOUSE_BUTTON_RIGHT){
            if(action == GLFW_PRESS){
                mousestatus.RIGHT_MOUSE_PRESSED = true;
            }else{
                mousestatus.RIGHT_MOUSE_PRESSED = false;
            }
        }
    }

    double Window::getMouseX(){
        return -1.0 + 2.0*mouseX/window_width;
    }

    double Window::getMouseY(){
        return -(-1.0 + 2.0* mouseY/window_height);
    }

    double Window::getMouseYAspectScaled(){
        return getMouseY()*getInverseAspectRatio();
    }

    std::vector<ShaderUniform> Window::getWindowUniforms(){
        if(!window_uniforms_up_to_date){
            recalculateWindowUniforms();
        }

        return window_uniforms;
    }

    void Window::recalculateWindowUniforms(){
        std::vector<ShaderUniform> newWindowUniformList;
        
        ShaderUniform aspectratio_uniform;
        aspectratio_uniform.target.name = "aspectRatio";
        aspectratio_uniform.target.type = OPENGL_FLOAT;
        aspectratio_uniform.value.f = getAspectRatio();

        ShaderUniform invaspectratio_uniform;
        invaspectratio_uniform.target.name = "inverseAspectRatio";
        invaspectratio_uniform.target.type = OPENGL_FLOAT;
        invaspectratio_uniform.value.f = getInverseAspectRatio();

        newWindowUniformList.push_back(aspectratio_uniform);
        newWindowUniformList.push_back(invaspectratio_uniform);

        window_uniforms = newWindowUniformList;
    }

    void Window::swapBuffers(){
        if(!windowActive){
            return;
        }

        glfwSwapBuffers(window);
    }

    PLUSH_helpers::KeyboardStatus* Window::getKeyboardStatusPointer(){
        return &keyboardstatus;
    }

    PLUSH_helpers::MouseStatus* Window::getMouseStatusPointer(){
        return &mousestatus;
    }
}