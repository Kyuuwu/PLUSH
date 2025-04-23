#ifndef UNIFORMRESOLVER_HPP
#define UNIFORMRESOLVER_HPP

#include "PlushGraphics.hpp"
#include "Shader/ManagedShader.hpp"
#include <memory>

namespace PlushGraphics {
    class UniformResolver{
        public:
            virtual ~UniformResolver() = 0; // prevent instantiation

            virtual void resolveUniformRequirements(ManagedShader shader) {
                #pragma unused(shader) // default behavior is no-op
            }

            virtual UniquePtrUniformResolver duplicateSelf() const = 0; // must be implemented per derived class
    };
    inline UniformResolver::~UniformResolver(){} // still allows derived classes to destroy base when destroyed
}

#endif // UNIFORMRESOLVER_HPP
