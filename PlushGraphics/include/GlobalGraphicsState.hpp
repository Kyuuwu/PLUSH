#ifndef PLUSHGRAPHICSOPENGL_HPP
#define PLUSHGRAPHICSOPENGL_HPP

#include "PlushGraphics.hpp"

#include "PlushUtilException.hpp"
#include "Shader/ShaderRegistry.hpp"
#include "ModelData/ModelDataRegistry.hpp"
#include "ModelInstance/ModelInstanceRegistry.hpp"
#include "Window/Window.hpp"
#include "Window/WindowIdentifier.hpp"
#include "Window/WindowRegistry.hpp"
#include "Texture2D/Texture2DRegistry.hpp"
#include "Drawable/DrawableRegistry.hpp"
#include "GraphicsLayer/GraphicsLayerRegistry.hpp"
#include <optional>

namespace PlushGraphics {
    class GlobalGraphicsState{
        public:
            inline static ShaderRegistry shaderRegistry;
            inline static ModelDataRegistry modelDataRegistry;
            inline static ModelInstanceRegistry modelInstanceRegistry;
            inline static WindowRegistry windowRegistry;
            inline static Texture2DRegistry textureRegistry;
            inline static DrawableRegistry drawableRegistry;
            inline static GraphicsLayerRegistry graphicsLayerRegistry;

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
            static ManagedGraphicsLayer getGraphicsLayer(GraphicsLayerIdentifier identifier){
                return graphicsLayerRegistry.getItem(identifier);
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
            static bool isGraphicsLayerLoaded(GraphicsLayerIdentifier identifier){
                return graphicsLayerRegistry.isItemLoaded(identifier);
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
            static GraphicsLayerIdentifier loadGraphicsLayer(GraphicsLayerSpec spec){
                return graphicsLayerRegistry.loadItem(spec);
            }

            static void switchContextToActiveWindow(){
                if(activeWindowId.has_value()){
                    switchContextToWindow(*activeWindowId);
                }
            }

            static void switchContextToWindow(WindowIdentifier windowID){
                // try{
                //     windowRegistry.getItem(windowID).switchContextToWindow();
                // } catch(PlushUtil::PlushUtilException e){
                //     if ((e == PlushUtil::PlushUtilException::ITEM_NOT_LOADED_IN_REGISTRY) && (windowID == dummyWindowIdentifier)){
                //         std::cout << "Attempted to switch context before first window created, exception suppressed." << std::endl;
                //         return; // if first context is not loaded, don't thow errors from context switch request
                //     }
                //     else{
                //         throw(e);
                //     }
                // }
                windowRegistry.getItem(windowID).switchContextToWindow();
                activeWindowId = windowID;
                // activeWindowIdentifier = windowID;
            }

            static WindowIdentifier getActiveWindowIdentifier() { return *activeWindowId; } // can cause error if no active window yet TBD

            static void initializeOpenGL();
            static void terminateOpenGL();

            static GLFWwindow* getRootContext() { return rootContext; }

            static drawableID_t getNextUniqueDrawableID(){
                drawableID_t result = nextUniqueDrawableID;
                nextUniqueDrawableID++;
                return result;
            }

            static graphicsLayerID_t getNextUniqueGraphicsLayerID(){
                graphicsLayerID_t result = nextUniqueGraphicsLayerID;
                nextUniqueGraphicsLayerID++;
                return result;
            }

        private:
            // inline static const WindowIdentifier dummyWindowIdentifier = WindowIdentifier("QQQ NOEXCEPT");

            // inline static WindowIdentifier activeWindowIdentifier = dummyWindowIdentifier;
            inline static std::optional<WindowIdentifier> activeWindowId;

            inline static GLFWwindow* rootContext = NULL;

            inline static drawableID_t nextUniqueDrawableID = 0;
            inline static graphicsLayerID_t nextUniqueGraphicsLayerID = 0;
    };
}

#endif // PLUSHGRAPHICSOPENGL_HPP
