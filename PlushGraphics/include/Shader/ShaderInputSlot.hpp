#ifndef SHADERINPUTSLOT_HPP
#define SHADERINPUTSLOT_HPP

#include "PlushGraphics.hpp"
#include "ShaderInputSlotIdentifier.hpp"
#include <cstdint>

namespace PlushGraphics {
    class ShaderMetadata::ShaderInputSlot{
        public:
            ShaderInputSlot(ShaderInputSlotIdentifier _identifier, shaderSlotLocation_t _location)
            : identifier(_identifier), location(_location) {}

            const ShaderInputSlotIdentifier identifier;
            const shaderSlotLocation_t location;

            // ShaderInputSlotIdentifier getIdentifier() const { return identifier; }
            // shaderSlotLocation_t getLocation() const { return location; }
            
        private:
    };
}

#endif // SHADERINPUTSLOT_HPP
