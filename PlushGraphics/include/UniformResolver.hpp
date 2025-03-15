#ifndef UNIFORMRESOLVER_HPP
#define UNIFORMRESOLVER_HPP

#include "PlushGraphics.hpp"
#include "ManagedShader.hpp"

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
                void resolveUniformRequirements(ManagedShader shader) override {
                    #pragma unused(shader)
                } // no-op
        };

        class PreloadedUniformsResolver : public UniformResolver{ // dumps provided list of payloads into shader
            public:
                PreloadedUniformsResolver(std::vector<ShaderMetadata::ShaderUniformPayload> _payloads):
                payloads(_payloads){}

                void resolveUniformRequirements(ManagedShader shader) override{
                    for(ShaderMetadata::ShaderUniformPayload payload : payloads){
                        shader.tryToSetUniform(payload);
                    }
                }

            private:
                std::vector<ShaderMetadata::ShaderUniformPayload> payloads;
        };
    }
}

#endif // UNIFORMRESOLVER_HPP
