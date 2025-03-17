#ifndef PLUSHGRAPHICSOPENGL_HPP
#define PLUSHGRAPHICSOPENGL_HPP

#include "Texture2D/ManagedTexture2D.hpp"
#include "PlushGraphics.hpp"

#include "Shader/ShaderRegistry.hpp"
#include "ModelData/ModelDataRegistry.hpp"
#include "ModelInstance/ModelInstanceRegistry.hpp"
#include "Texture2D/Texture2D.hpp"
#include "Texture2D/Texture2DIdentifier.hpp"
#include "Texture2D/Texture2DSpec.hpp"
#include "Window/WindowRegistry.hpp"
#include "Texture2D/Texture2DRegistry.hpp"
#include "Drawable/DrawableRegistry.hpp"

namespace PlushGraphics {
    class GlobalGraphicsState{
        public:
            inline static ShaderRegistry shaderRegistry;
            inline static ModelDataRegistry modelDataRegistry;
            inline static ModelInstanceRegistry modelInstanceRegistry;
            inline static WindowRegistry windowRegistry;
            inline static Texture2DRegistry textureRegistry;
            inline static DrawableRegistry drawableRegistry;

            static ManagedShader getShader(ShaderIdentifier identifier){
                return shaderRegistry.getItem(identifier);
            }
            static ManagedModelData getModelData(ModelDataIdentifier identifier){
                return modelDataRegistry.getItem(identifier);
            }
            static ManagedModelInstance getModelInstance(ModelInstanceIdentifier identifier){
                return modelInstanceRegistry.getItem(identifier);
            }
            static ManagedWindow getWindow(WindowIdentifier identifier){
                return windowRegistry.getItem(identifier);
            }
            static ManagedTexture2D getTexture2D(Texture2DIdentifier identifier){
                return textureRegistry.getItem(identifier);
            }
            static ManagedDrawable getDrawable(DrawableIdentifier identifier){
                return drawableRegistry.getItem(identifier);
            }

            static bool isShaderLoaded(ShaderIdentifier identifier){
                return shaderRegistry.isItemLoaded(identifier);
            }
            static bool isModelDataLoaded(ModelDataIdentifier identifier){
                return modelDataRegistry.isItemLoaded(identifier);
            }
            static bool isModelInstanceLoaded(ModelInstanceIdentifier identifier){
                return modelInstanceRegistry.isItemLoaded(identifier);
            }
            static bool isWindowLoaded(WindowIdentifier identifier){
                return windowRegistry.isItemLoaded(identifier);
            }
            static bool isTexture2DLoaded(Texture2DIdentifier identifier){
                return textureRegistry.isItemLoaded(identifier);
            }
            static bool isDrawableLoaded(DrawableIdentifier identifier){
                return drawableRegistry.isItemLoaded(identifier);
            }

            static ShaderIdentifier loadShader(ShaderSpec spec){
                return shaderRegistry.loadItem(spec);
            }
            static ModelDataIdentifier loadModelData(ModelDataSpec spec){
                return modelDataRegistry.loadItem(spec);
            }
            static ModelInstanceIdentifier loadModelInstance(ModelInstanceSpec spec){
                return modelInstanceRegistry.loadItem(spec);
            }
            static WindowIdentifier loadWindow(WindowSpec spec){
                return windowRegistry.loadItem(spec);
            }
            static Texture2DIdentifier loadTexture2D(Texture2DSpec spec){
                return textureRegistry.loadItem(spec);
            }
            static DrawableIdentifier loadDrawable(DrawableSpec spec){
                return drawableRegistry.loadItem(spec);
            }

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
