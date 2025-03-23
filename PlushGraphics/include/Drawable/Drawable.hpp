#ifndef DRAWABLE2_HPP
#define DRAWABLE2_HPP

#include "ModelInstance/ManagedModelInstance.hpp"
#include "PlushGraphics.hpp"
#include "UniformResolver.hpp"
#include <memory>
#include "DrawableIdentifier.hpp"

namespace PlushGraphics {
    class Drawable{
        public:
            using Spec = DrawableSpec;
            using Identifier = DrawableIdentifier;

            template<UniResDerived T>
            Drawable(T&& ur, ManagedModelInstance _modelInstance) : 
                modelInstance(_modelInstance), // move creates dynamic T from static
                resolver(new T(std::move(ur))) {}

            template<UniResDerived T>
            Drawable(const T& ur, ManagedModelInstance _modelInstance) : 
                modelInstance(_modelInstance), // copies dynamic T from static
                resolver(new T(ur)) {}
            
            Drawable(DrawableSpec spec);

            void _setModelInstance(ManagedModelInstance _modelInstance) { // CONTRACT: drawables can only change the source modeldata, not the targeted shader
                if(_modelInstance.getShader().getIdentifier() != modelInstance.getShader().getIdentifier()){
                    throw(PlushGraphicsException::CANNOT_CHANGE_DRAWABLE_SHADER);
                }
                modelInstance = _modelInstance;
            }

            void _draw();

            DrawableIdentifier getIdentifier() const { return identifier; }

            ManagedShader _getModelInstanceShader(){
                return modelInstance.getShader();
            }

        private:
            DrawableIdentifier identifier;

            ManagedModelInstance modelInstance;

            SharedPtrUniformResolver resolver;
    };
}

#endif // DRAWABLE2_HPP
