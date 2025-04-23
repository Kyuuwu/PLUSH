#ifndef PRELOADEDUNIFORMRESOLVER_HPP
#define PRELOADEDUNIFORMRESOLVER_HPP

#include "PlushGraphics.hpp"
#include "UniformResolver.hpp"

namespace PlushGraphics {
    namespace UniformResolvers {
    
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

#endif // PRELOADEDUNIFORMRESOLVER_HPP
