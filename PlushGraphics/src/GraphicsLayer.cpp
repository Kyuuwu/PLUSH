#include "GraphicsLayer/GraphicsLayer.hpp"
#include "GraphicsLayer/GraphicsLayerSpec.hpp"
#include "Drawable/ManagedDrawable.hpp"
#include "Shader/ManagedShader.hpp"
#include <cstddef>
#include <set>

namespace PlushGraphics {
    GraphicsLayer::GraphicsLayer(GraphicsLayerSpec spec)
        : resolver(spec.resolver->duplicateSelf())
    {
        
    }

    void GraphicsLayer::_performDrawCycle() {
        for(ManagedShader shader : _getNecessaryShaders()){
            // tell shader its being uniform resolved by layer
            shader.clearLayerLevelUniforms();
            shader.prepareForLayerUniforms();
            shader.acceptUniformResolver(resolver);
        }
    
        // prep and sort drawables?
    
        // draw drawables
        for(ManagedDrawable drawable : drawables){
            drawable.draw();
        }
    }

    void GraphicsLayer::_addDrawable(ManagedDrawable drawable) {
        drawables.push_back(drawable);
    }

    void GraphicsLayer::_removeDrawable(ManagedDrawable drawable) {
        for(size_t i = 0; i < drawables.size(); i++){
            if(drawable.getIdentifier() == drawables[i].getIdentifier()){
                drawables.erase(drawables.begin() + i);
                return; // assumes only one copy of drawable
            }
        }
    }
    
    std::set<ManagedShader> GraphicsLayer::_getNecessaryShaders() {
        return getNecessaryShadersFromDrawables(); // for now just directly obtain
    }

    std::set<ManagedShader> GraphicsLayer::getNecessaryShadersFromDrawables() {
        std::set<ManagedShader> shaders;

        for(ManagedDrawable drawable : drawables){
            shaders.insert(drawable.getModelInstanceShader());
        }

        return shaders;
    }

}

