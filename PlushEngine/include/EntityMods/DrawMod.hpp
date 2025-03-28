#ifndef DRAWMOD_HPP
#define DRAWMOD_HPP

#include "../EngineInterfaces/BaseEntityMod.hpp"
#include "Drawable/ManagedDrawable.hpp"
#include "EngineInterfaces/ControlsDrawable.hpp"
#include "Entity/ManagedEntity.hpp"
#include "GraphicsLayer/ManagedGraphicsLayer.hpp"
#include "ModelInstance/ManagedModelInstance.hpp"
#include "PlushUtil.hpp"
#include "Shader/ManagedShader.hpp"
#include "Texture2D/ManagedTexture2D.hpp"
#include "Slot.hpp"

namespace PlushEngine {
    namespace EntityMods {
        class DrawMod : public EngineInterfaces::BaseEntityMod, public EngineInterfaces::ControlsDrawable{
            public:
                DrawMod(ManagedEntity owningEntity, PlushGraphics::ManagedModelInstance modelInstance, PlushGraphics::ManagedGraphicsLayer layer);

                void resolveUniformRequirements(PlushGraphics::ManagedShader shader) override;

                void setModelInstance(PlushGraphics::ManagedModelInstance _instance) override;
                void moveDrawableToLayer(PlushGraphics::ManagedGraphicsLayer _layer) override;
                void setPrimaryTexture(PlushGraphics::ManagedTexture2D _texture) override;

            private:
                PlushGraphics::ManagedDrawable drawable;
                PlushGraphics::ManagedGraphicsLayer currentLayer;

                PlushUtil::Slot<PlushGraphics::ManagedTexture2D> primaryTextureSlot;
        };
    }
}

#endif // DRAWMOD_HPP
