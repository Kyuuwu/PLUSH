#ifndef SHADERSPEC_HPP
#define SHADERSPEC_HPP

#include "PlushGraphics.hpp"
#include <string>
#include <vector>
#include <map>

namespace PlushGraphics {
    class ShaderSpec{
        public:
            std::string vertexShaderSource();
            std::string fragmentShaderSource();

            std::vector<ShaderMetadata::ShaderUniformSlot> shaderUniformSlots();
            std::vector<ShaderMetadata::ShaderInputSlot> shaderInputSlots();
            std::map<ShaderMetadata::ShaderUniformSlotIdentifier, size_t> shaderUniformSlotIndexMap();

        private:

    };
}

#endif // SHADERSPEC_HPP
