#ifndef UNIFORMRESOLVER_HPP
#define UNIFORMRESOLVER_HPP

#include "ManagedShader.hpp"
#include "PlushGraphics.hpp"

namespace PlushGraphics {
    class UniformResolver{
        public:
            UniformResolver(){}
            virtual ~UniformResolver(){}

            virtual void resolveUniformRequirements(ManagedShader shader) = 0;
    };

    namespace UniformResolvers { // various PlushGraphics-level uniform resolvers

        class NoOpResolver : public UniformResolver{ // no-op resolver, does not attempt to resolve uniforms
            public:
                void resolveUniformRequirements(ManagedShader shader) override {} // no-op
        };
    }
}

#endif // UNIFORMRESOLVER_HPP
