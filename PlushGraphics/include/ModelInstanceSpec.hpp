#ifndef MODELINSTANCESPEC_HPP
#define MODELINSTANCESPEC_HPP

#include "ModelDataIdentifier.hpp"
#include "ShaderIdentifier.hpp"

namespace PlushGraphics {
    class ModelInstanceSpec{
        public:
            ModelInstanceSpec(ModelDataIdentifier _modelDataIdentifier, ShaderIdentifier _shaderIdentifier)
            : modelDataIdentifier(_modelDataIdentifier), shaderIdentifier(_shaderIdentifier) {}

            ModelDataIdentifier getModelDataIdentifier() const { return modelDataIdentifier; }
            ShaderIdentifier getShaderIdentifier() const { return shaderIdentifier; }

        private:
            ModelDataIdentifier modelDataIdentifier;
            ShaderIdentifier shaderIdentifier;
    };
}

#endif // MODELINSTANCESPEC_HPP
