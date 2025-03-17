#ifndef SHADERSPEC_HPP
#define SHADERSPEC_HPP

#include "PlushGraphics.hpp"
#include <string>
#include <vector>
#include <map>

namespace PlushGraphics {
    class ShaderSpec{
        public:
            ShaderSpec(std::string _shaderName);

            std::string vertexShaderSource();
            std::string fragmentShaderSource();

            std::vector<ShaderMetadata::ShaderUniformSlotIdentifier> shaderUniformSlotIdentifiers();
            std::vector<ShaderMetadata::ShaderInputSlot> shaderInputSlots();

            std::string shaderName();

        private:
            std::string shaderNameString;
            std::string vertexShaderSourceString;
            std::string fragmentShaderSourceString;
            std::vector<ShaderMetadata::ShaderUniformSlotIdentifier> shaderUniformSlotIdentifiersVector;
            std::vector<ShaderMetadata::ShaderInputSlot> shaderInputSlotsVector;

    };
}

#endif // SHADERSPEC_HPP
