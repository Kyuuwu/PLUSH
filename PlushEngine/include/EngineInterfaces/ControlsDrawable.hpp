#ifndef CONTROLSDRAWABLE_HPP
#define CONTROLSDRAWABLE_HPP

#include "GraphicsLayer/ManagedGraphicsLayer.hpp"
#include "ModelInstance/ManagedModelInstance.hpp"
#include "Texture2D/ManagedTexture2D.hpp"
namespace PlushEngine {
    namespace EngineInterfaces {
        class ControlsDrawable{
            public:
                virtual void setModelInstance(PlushGraphics::ManagedModelInstance _modelInstance) = 0;
                virtual void moveDrawableToLayer(PlushGraphics::ManagedGraphicsLayer _layer) = 0;
                virtual void setPrimaryTexture(PlushGraphics::ManagedTexture2D _texture) = 0;
        };
    }
}

#endif // CONTROLSDRAWABLE_HPP
