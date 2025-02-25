#ifndef SHADERUNIFORMSLOT_HPP
#define SHADERUNIFORMSLOT_HPP

#include "PlushGraphics.hpp"
#include "ShaderUniformSlotIdentifier.hpp"
#include <cstdint>

namespace PlushGraphics {
    class ShaderMetadata::ShaderUniformSlot{
        public:
            ShaderUniformSlot(ShaderUniformSlotIdentifier _identifier, shaderSlotLocation_t _location)
            : identifier(_identifier), location(_location)
            {}

            ShaderUniformSlotIdentifier getIdentifier() const { return identifier; }
            shaderSlotLocation_t getLocation() const { return location; }

        private:
            ShaderUniformSlotIdentifier identifier;
            shaderSlotLocation_t location;
    };
}

#endif // SHADERUNIFORMSLOT_HPP
