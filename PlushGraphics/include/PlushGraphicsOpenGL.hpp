#ifndef PLUSHGRAPHICSOPENGL_HPP
#define PLUSHGRAPHICSOPENGL_HPP

#include "PlushGraphics.hpp"
#include "ShaderRegistry.hpp"
#include "ModelDataRegistry.hpp"
#include "ModelInstanceRegistry.hpp"
#include "WindowIdentifier.hpp"
#include "WindowRegistry.hpp"

namespace PlushGraphics {
    class GlobalGraphicsState{
        public:
            inline static ShaderRegistry shaderRegistry;
            inline static ModelDataRegistry modelDataRegistry;
            inline static ModelInstanceRegistry modelInstanceRegistry;
            inline static WindowRegistry windowRegistry;

            static void switchContextToWindow(WindowIdentifier windowID){
                windowRegistry.getItem(windowID).switchContextToWindow();
                activeWindowIdentifier = windowID;
            }

            static WindowIdentifier getActiveWindowIdentifier() { return activeWindowIdentifier; }

            static void initializeOpenGL();
            static void terminateOpenGL();

            static GLFWwindow* getRootContext() { return rootContext; }

            static drawableID_t getNextUniqueDrawableID(){
                drawableID_t result = nextUniqueDrawableID;
                nextUniqueDrawableID++;
                return result;
            }

        private:
            inline static WindowIdentifier activeWindowIdentifier = WindowIdentifier("blah");

            inline static GLFWwindow* rootContext = NULL;

            inline static drawableID_t nextUniqueDrawableID = 0;
    };
}

#endif // PLUSHGRAPHICSOPENGL_HPP
