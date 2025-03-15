#ifndef DRAWABLESPEC_HPP
#define DRAWABLESPEC_HPP

#include "ManagedModelInstance.hpp"
#include "PlushGraphics.hpp"
#include <memory>
#include "UniformResolver.hpp"

namespace PlushGraphics {
    class DrawableSpec{
        public:
            friend class Drawable;

            template<UniResDerived T>
            DrawableSpec(T&& ur, ManagedModelInstance _modelInstance) : 
                modelInstance(_modelInstance), // move creates dynamic T from static
                resolver(new T(std::move(ur))) {}

            template<UniResDerived T>
            DrawableSpec(const T& ur, ManagedModelInstance _modelInstance) : 
                modelInstance(_modelInstance), // copies dynamic T from static
                resolver(new T(ur)) {}

            DrawableSpec(const DrawableSpec& other):
                modelInstance(other.modelInstance),
                resolver(other.resolver->duplicateSelf()){}

        private:
            ManagedModelInstance modelInstance;
            std::unique_ptr<UniformResolver> resolver;
    };
}

#endif // DRAWABLESPEC_HPP
