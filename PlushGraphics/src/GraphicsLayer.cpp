#include "GraphicsLayer/GraphicsLayer.hpp"
#include "GraphicsLayer/GraphicsLayerSpec.hpp"
#include "Drawable/ManagedDrawable.hpp"
#include "Shader/ManagedShader.hpp"
#include <set>

namespace PlushGraphics {
    GraphicsLayer::GraphicsLayer(GraphicsLayerSpec spec)
        : resolver(spec.resolver->duplicateSelf())
    {
        
    }

    void GraphicsLayer::_performDrawCycle() {
        for(ManagedShader shader : getNecessaryShaders()){
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
    
    std::set<ManagedShader> GraphicsLayer::getNecessaryShaders() {
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

