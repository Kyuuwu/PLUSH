#ifndef DRAWABLESPEC_HPP
#define DRAWABLESPEC_HPP

#include "Callable.hpp"
#include "ModelInstance/ManagedModelInstance.hpp"
#include "PlushGraphics.hpp"
#include <memory>
#include "PlushUtil.hpp"
#include "UniformResolver.hpp"
#include "UniformResolvers/NoOpResolver.hpp"

namespace PlushGraphics {
    class DrawableSpec{
        public:
            friend class Drawable;

            DrawableSpec(ManagedModelInstance _modelInstance):
                modelInstance(_modelInstance),
                resolver(new UniformResolvers::NoOpResolver()),
                predrawCall(new PlushUtil::NoOpCallable()){}

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
            UniquePtrUniformResolver resolver;
            PlushUtil::UniquePtrCallable predrawCall;
    };
}

#endif // DRAWABLESPEC_HPP
