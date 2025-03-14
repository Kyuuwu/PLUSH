#ifndef SHADERUNIFORMSLOT_HPP
#define SHADERUNIFORMSLOT_HPP

#include "PlushGraphics.hpp"
#include "ShaderUniformSlotIdentifier.hpp"
#include "ShaderUniformSlotFulfillmentState.hpp"
#include <cstdint>

namespace PlushGraphics {
    class ShaderMetadata::ShaderUniformSlot{
        public:
            // friend class PlushGraphics::Shader;

            ShaderUniformSlot(ShaderUniformSlotIdentifier _identifier, shaderSlotLocation_t _location)
            : identifier(_identifier), location(_location)
            {}

            const ShaderUniformSlotIdentifier identifier;
            const shaderSlotLocation_t location;

            ShaderUniformSlotFulfillmentState fulfillmentState;

            // ShaderUniformSlotIdentifier getIdentifier() const { return identifier; }
            // shaderSlotLocation_t getLocation() const { return location; }

        private:
    };
}

#endif // SHADERUNIFORMSLOT_HPP
