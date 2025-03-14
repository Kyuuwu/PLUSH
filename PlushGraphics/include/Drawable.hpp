#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "ManagedModelInstance.hpp"
#include "PlushGraphics.hpp"
#include "UniformResolver.hpp"
#include <memory>

namespace PlushGraphics {
    template<typename T>
    concept UniResDerived =
        requires {
            requires std::derived_from<T, UniformResolver>;
        };

    class Drawable{
        public:
            template<UniResDerived T>
            Drawable(T&& ur, ManagedModelInstance _modelInstance) : 
                resolver(new T(std::move(ur))),
                modelInstance(_modelInstance) {}

            template<UniResDerived T>
            Drawable(const T& ur, ManagedModelInstance _modelInstance) : 
                resolver(new T(ur)),
                modelInstance(_modelInstance) {}

            void setModelInstance(ManagedModelInstance _modelInstance) {
                modelInstance = _modelInstance;
            }

            void draw();

        private:
            std::unique_ptr<UniformResolver> resolver;

            ManagedModelInstance modelInstance;
    };
}

#endif // DRAWABLE_HPP
