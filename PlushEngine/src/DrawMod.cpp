#include "EntityMods/DrawMod.hpp"
#include "GlobalGraphicsState.hpp"
#include "OpenGL_Type.hpp"
#include "OpenGL_Value.hpp"
#include "PlushEngine.hpp"
#include "EngineUniformResolvers/EntityUniformResolver.hpp"
#include "Shader/ShaderUniformPayload.hpp"
#include "Shader/ShaderUniformSlotIdentifier.hpp"
#include "UniformResolvers/NoOpResolver.hpp"

namespace PlushEngine {
    namespace EntityMods {

        DrawMod::DrawMod(PlushGraphics::ManagedModelInstance modelInstance, PlushGraphics::ManagedGraphicsLayer layer)
            : drawable(PlushGraphics::GlobalGraphicsState::getDrawable(PlushGraphics::GlobalGraphicsState::loadDrawable(
                PlushGraphics::DrawableSpec(PlushGraphics::UniformResolvers::NoOpResolver(), modelInstance)))),
              currentLayer(layer)
        {
            currentLayer.addDrawable(drawable);
        }

        DrawMod::DrawMod(ManagedEntity owningEntity, PlushGraphics::ManagedModelInstance modelInstance, PlushGraphics::ManagedGraphicsLayer layer)
            : BaseEntityMod(owningEntity),
              drawable(PlushGraphics::GlobalGraphicsState::getDrawable(PlushGraphics::GlobalGraphicsState::loadDrawable(
                PlushGraphics::DrawableSpec(EngineUniformResolvers::EntityUniformResolver(owningEntity), modelInstance)))),
              currentLayer(layer)
        {
            currentLayer.addDrawable(drawable);
        }

        void DrawMod::resolveUniformRequirements(PlushGraphics::ManagedShader shader) {
            if(primaryTextureSlot.has_value()){
                primaryTextureSlot->bindToTextureUnit(2);
                PlushGraphics::ShaderMetadata::ShaderUniformPayload texturePayload(
                    PlushGraphics::ShaderMetadata::ShaderUniformSlotIdentifier(
                        "texture1", PlushGraphics::OpenGL_Type::SAMPLER2D
                    ),
                    PlushGraphics::OpenGL_Value::create_sampler_2D(2)
                );
                shader.setUniformNew(texturePayload);
            }
        }

        void DrawMod::setModelInstance(PlushGraphics::ManagedModelInstance _instance) {
            drawable.setModelInstance(_instance);
        }

        void DrawMod::moveDrawableToLayer(PlushGraphics::ManagedGraphicsLayer _layer) {
            currentLayer.removeDrawable(drawable);
            _layer.addDrawable(drawable);
            currentLayer = _layer;
        }

        void DrawMod::setPrimaryTexture(PlushGraphics::ManagedTexture2D _texture) {
            primaryTextureSlot = _texture;
        }
        
    }
}