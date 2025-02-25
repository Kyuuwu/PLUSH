#ifndef SHADERUNIFORMVALUE_HPP
#define SHADERUNIFORMVALUE_HPP

#include "PlushGraphics.hpp"
#include "ShaderUniformSlotIdentifier.hpp"
#include "OpenGL_Value.hpp"

namespace PlushGraphics {
    class ShaderMetadata::ShaderUniformPayload{
        friend class PlushGraphics::Shader;

        public:
            ShaderUniformPayload(ShaderUniformSlotIdentifier _targetSlotIdentifier, OpenGL_Value _value)
            : targetSlotIdentifier(_targetSlotIdentifier), value(_value){}
            
            ShaderUniformSlotIdentifier getTargetSlotIdentifier() const { return targetSlotIdentifier; }

        private:
            void setUniformAtLocation(shaderSlotLocation_t location);

            ShaderUniformSlotIdentifier targetSlotIdentifier;
            OpenGL_Value value;
        
    };
}

#endif // SHADERUNIFORMVALUE_HPP
