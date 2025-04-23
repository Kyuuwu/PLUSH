#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GraphicsLayer/ManagedGraphicsLayer.hpp"
#include "OpenGL.h"
#include "PlushGraphics.hpp"
#include "UniformResolver.hpp"
#include "WindowIdentifier.hpp"
#include <cstddef>
#include <vector>
#include "WindowSettings.hpp"

namespace PlushGraphics {
    class Window{
        public:
            friend class GlobalGraphicsState;
            friend class WindowRegistry;
            friend class ManagedWindow;

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

            void _clearGraphicsLayers(){
                graphicsLayers = std::vector<ManagedGraphicsLayer>();
            }

            void _updateWindowSize(int width, int height);

            double _getAspectRatio(){
                return settings.windowWidth / settings.windowHeight;
            }

        private:
            WindowIdentifier identifier;

            WindowSettings settings;

            GLFWwindow* windowPointer;

            std::vector<ManagedGraphicsLayer> graphicsLayers;

            SharedPtrUniformResolver resolver;
    };
}

#endif // WINDOW_HPP
