#ifndef SHADERUNIFORMVALUE_HPP
#define SHADERUNIFORMVALUE_HPP

#include "PlushGraphics.hpp"
#include "ShaderUniformSlotIdentifier.hpp"

namespace PlushGraphics {
    class ShaderMetadata::ShaderUniformValue{
        friend class PlushGraphics::Shader;

        public:
            ShaderUniformSlotIdentifier getTargetSlotIdentifier() const { return targetSlotIdentifier; }

        private:
            void setUniformAtLocation(shaderSlotLocation_t location);

            ShaderUniformSlotIdentifier targetSlotIdentifier;
        
    };
}

#endif // SHADERUNIFORMVALUE_HPP
