#ifndef DRAWMOD_HPP
#define DRAWMOD_HPP

#include "../EngineInterfaces/BaseEntityMod.hpp"
#include "Drawable/ManagedDrawable.hpp"
#include "EngineInterfaces/ControlsDrawable.hpp"
#include "Entity/ManagedEntity.hpp"
#include "GraphicsLayer/ManagedGraphicsLayer.hpp"
#include "ModelInstance/ManagedModelInstance.hpp"
#include "Shader/ManagedShader.hpp"
#include "Texture2D/ManagedTexture2D.hpp"
#include <optional>
#include "EngineUniformResolvers/EntityUniformResolver.hpp"

namespace PlushEngine {
    namespace EntityMods {
        class DrawMod : public EngineInterfaces::BaseEntityMod, public EngineInterfaces::ControlsDrawable{
            public:
                DrawMod(PlushGraphics::ManagedModelInstance modelInstance, PlushGraphics::ManagedGraphicsLayer layer);

                DrawMod(ManagedEntity owningEntity, PlushGraphics::ManagedModelInstance modelInstance, PlushGraphics::ManagedGraphicsLayer layer);

                void resolveUniformRequirements(PlushGraphics::ManagedShader shader) override;

                void setModelInstance(PlushGraphics::ManagedModelInstance _instance) override;
                void moveDrawableToLayer(PlushGraphics::ManagedGraphicsLayer _layer) override;
                void setPrimaryTexture(PlushGraphics::ManagedTexture2D _texture) override;
                DrawMod&& withPrimaryTexture(PlushGraphics::ManagedTexture2D _texture) {
                    setPrimaryTexture(_texture);
                    return std::move(*this);
                }

            protected:
                void processNewOwningEntity() override{
                    drawable.setUniformResolver(EngineUniformResolvers::EntityUniformResolver(*owningEntity));
                }

            private:
                PlushGraphics::ManagedDrawable drawable;
                PlushGraphics::ManagedGraphicsLayer currentLayer;

                std::optional<PlushGraphics::ManagedTexture2D> primaryTextureSlot;
        };
    }
}

#endif // DRAWMOD_HPP
