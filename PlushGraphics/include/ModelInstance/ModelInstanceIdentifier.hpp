#ifndef MODELINSTANCEIDENTIFIER_HPP
#define MODELINSTANCEIDENTIFIER_HPP

#include "../ModelData/ModelDataIdentifier.hpp"
#include "../Shader/ShaderIdentifier.hpp"
#include "ModelInstanceSpec.hpp"

namespace PlushGraphics {
    class ModelInstanceIdentifier{
        public:
            ModelInstanceIdentifier(ModelDataIdentifier _modelDataIdentifier, ShaderIdentifier _shaderIdentifier):
            modelDataIdentifier(_modelDataIdentifier), shaderIdentifier(_shaderIdentifier){}
            
            ModelInstanceIdentifier(ModelInstanceSpec spec):
            ModelInstanceIdentifier(spec.getModelData().getIdentifier(), spec.getShader().getIdentifier()){}

            bool operator<(const ModelInstanceIdentifier& other) const{
                if(modelDataIdentifier < other.modelDataIdentifier){
                    return true;
                }
                if(other.modelDataIdentifier < modelDataIdentifier){
                    return false;
                }
                return shaderIdentifier < other.shaderIdentifier;
            } // sort by ModelData identifier first, then by shader identifier

            ShaderIdentifier getShaderIdentifier() const { return shaderIdentifier; }

            ModelDataIdentifier getModelDataIdentifier() const { return modelDataIdentifier; }

        private:
            ModelDataIdentifier modelDataIdentifier;
            ShaderIdentifier shaderIdentifier;
    };
}

#endif // MODELINSTANCEIDENTIFIER_HPP
