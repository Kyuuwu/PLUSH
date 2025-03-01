#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "OpenGL.h"
#include "PlushGraphics.hpp"
#include "WindowIdentifier.hpp"

namespace PlushGraphics {
    class Window{
        public:
            friend class OpenGL;

            using Identifier = WindowIdentifier;
            using Spec = WindowSpec;

            Window(WindowSpec windowbuilder);
            
            ~Window();

            Window(const Window&) = delete; // delete rule of 5s
            Window(Window&&) = delete;
            Window& operator=(const Window&) = delete;
            Window& operator=(Window&&) = delete;

            WindowIdentifier getIdentifier() const { return identifier; }

            bool getWindowShouldClose() const {
                return glfwWindowShouldClose(windowPointer);
            }

            void swapBuffers(){
                glfwSwapBuffers(windowPointer);
            }

            void switchContextToWindow(){
                glfwMakeContextCurrent(windowPointer);
            }

        private:
            WindowIdentifier identifier;

            GLFWwindow* windowPointer;
    };
}

#endif // WINDOW_HPP
