#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "OpenGL.h"
#include "PlushGraphics.hpp"
#include "UniformResolver.hpp"
#include "WindowIdentifier.hpp"
#include <vector>
#include "WindowSettings.hpp"

namespace PlushGraphics {
    class Window{
        public:
            friend class GlobalGraphicsState;

            using Identifier = WindowIdentifier;
            using Spec = WindowSpec;

            Window(WindowSpec windowbuilder);
            
            ~Window();

            Window(const Window&) = delete; // delete rule of 5s
            Window(Window&&) = delete;
            Window& operator=(const Window&) = delete;
            Window& operator=(Window&&) = delete;

            WindowIdentifier getIdentifier() const { return identifier; }

            bool _getWindowShouldClose() const {
                return glfwWindowShouldClose(windowPointer);
            }

            void _swapBuffers(){
                glfwSwapBuffers(windowPointer);
            }

            void _switchContextToWindow(){
                glfwMakeContextCurrent(windowPointer);
            }

            void _performDrawCycle();

            void _addGraphicsLayer(ManagedGraphicsLayer layer);

        private:
            WindowIdentifier identifier;

            WindowSettings settings;

            GLFWwindow* windowPointer;

            std::vector<ManagedGraphicsLayer> graphicsLayers;

            SharedPtrUniformResolver resolver;
    };
}

#endif // WINDOW_HPP
