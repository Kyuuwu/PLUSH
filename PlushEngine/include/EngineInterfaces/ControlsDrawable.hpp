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

                template<typename Self>
                Self&& withPrimaryTexture(this Self&& self, PlushGraphics::ManagedTexture2D _texture){
                    self.setPrimaryTexture(_texture);
                    return self;
                }
        };
    }
}

#endif // CONTROLSDRAWABLE_HPP
