#ifndef SHADERMEMENTO_HPP
#define SHADERMEMENTO_HPP

#include "Shader/ShaderUniformPayload.hpp"
#include <set>

namespace PlushGraphics {
    class ShaderMemento{
        public:
            friend class Shader;

            void setUniform(ShaderMetadata::ShaderUniformPayload payload, bool overrideExisting = true){
                if(overrideExisting){
                    setUniformOverride(payload);
                }else{
                    payloads.insert(payload); // doesn't override existing
                }
            }

        private:

            void setUniformOverride(ShaderMetadata::ShaderUniformPayload payload){
                // extracts pre-existing matching payload to override if one exists, otherwise creates empty node
                auto nodeHandle = payloads.extract(payload);
                if(nodeHandle.empty()){
                    payloads.insert(payload);
                }else{
                    nodeHandle.value() = payload;
                    payloads.insert(std::move(nodeHandle));
                }
            }

            std::set<ShaderMetadata::ShaderUniformPayload> payloads;
    };
}

#endif // SHADERMEMENTO_HPP
