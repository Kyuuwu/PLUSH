#ifndef PLUSHGRAPHICSOPENGL_HPP
#define PLUSHGRAPHICSOPENGL_HPP

#include "PlushGraphics.hpp"
#include "ShaderRegistry.hpp"
#include "ModelDataRegistry.hpp"
#include "WindowIdentifier.hpp"
#include "WindowRegistry.hpp"

namespace PlushGraphics {
    class OpenGL{
        public:
            inline static ShaderRegistry shaderRegistry;
            inline static ModelDataRegistry modelDataRegistry;
            inline static WindowRegistry windowRegistry;

            static void switchContextToWindow(WindowIdentifier windowID){
                windowRegistry.getItem(windowID).switchContextToWindow();
                activeWindowIdentifier = windowID;
            }

            static WindowIdentifier getActiveWindowIdentifier() { return activeWindowIdentifier; }

            static void initializeOpenGL();
            static void terminateOpenGL();

            static GLFWwindow* getRootContext() { return rootContext; }

        private:
            inline static WindowIdentifier activeWindowIdentifier = WindowIdentifier("blah");

            inline static GLFWwindow* rootContext = NULL;
    };
}

#endif // PLUSHGRAPHICSOPENGL_HPP
