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

    namespace UniformResolvers { // various PlushGraphics-level uniform resolvers

        class NoOpResolver : public UniformResolver{ // no-op resolver, does not attempt to resolve uniforms
            public:
                UniquePtrUniformResolver duplicateSelf() const override {
                    return UniquePtrUniformResolver(new NoOpResolver);
                }
        };

        class PreloadedUniformsResolver : public UniformResolver{ // dumps provided list of payloads into shader
            public:
                PreloadedUniformsResolver(std::vector<ShaderMetadata::ShaderUniformPayload> _payloads):
                payloads(_payloads){}

                PreloadedUniformsResolver(const PreloadedUniformsResolver& other):
                payloads(other.payloads){}

                UniquePtrUniformResolver duplicateSelf() const override{
                    return UniquePtrUniformResolver(new PreloadedUniformsResolver(*this));
                }

                void resolveUniformRequirements(ManagedShader shader) override{
                    for(ShaderMetadata::ShaderUniformPayload payload : payloads){
                        shader.setUniformNew(payload);
                    }
                }

            private:
                std::vector<ShaderMetadata::ShaderUniformPayload> payloads;
        };
    }
}

#endif // UNIFORMRESOLVER_HPP
