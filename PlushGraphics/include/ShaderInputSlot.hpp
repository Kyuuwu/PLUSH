#ifndef SHADERINPUTSLOT_HPP
#define SHADERINPUTSLOT_HPP

#include "PlushGraphics.hpp"
#include "ShaderInputSlotIdentifier.hpp"
#include <cstdint>

namespace PlushGraphics {
    class ShaderMetadata::ShaderInputSlot{
        public:
            ShaderInputSlotIdentifier getIdentifier() const { return identifier; }
            shaderSlotLocation_t getLocation() const { return location; }
            
        private:
            ShaderInputSlotIdentifier identifier;
            shaderSlotLocation_t location;
    };
}

#endif // SHADERINPUTSLOT_HPP
