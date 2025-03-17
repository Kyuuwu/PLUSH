#ifndef SHADERUNIFORMVALUE_HPP
#define SHADERUNIFORMVALUE_HPP

#include "PlushGraphics.hpp"
#include "PlushGraphicsException.hpp"
#include "ShaderUniformSlotIdentifier.hpp"
#include "ShaderUniformSlotFulfillmentState.hpp"
#include "OpenGL_Value.hpp"

namespace PlushGraphics {
    class ShaderMetadata::ShaderUniformPayload{
        friend class PlushGraphics::Shader;

        public:
            // ShaderUniformPayload(const ShaderUniformPayload& other):
            // targetSlotIdentifier(other.targetSlotIdentifier),
            // value(other.value)
            // {}

            // ShaderUniformPayload& operator=(const ShaderUniformPayload& other){
            //     value = other.value;
            //     targetSlotIdentifier = other.targetSlotIdentifier;
            //     return *this;
            // }

            ShaderUniformPayload(ShaderUniformSlotIdentifier _targetSlotIdentifier, OpenGL_Value _value)
            : targetSlotIdentifier(_targetSlotIdentifier), value(_value){
                if(!doesTypeMatch()){
                    throw(PlushGraphicsException::UNIFORM_PAYLOAD_TYPES_DONT_MATCH);
                }
            }
            
            ShaderUniformSlotIdentifier getTargetSlotIdentifier() const { return targetSlotIdentifier; }

            OpenGL_Value getValue() const { return value; }

            bool operator<(const ShaderUniformPayload& other) const { // < operator ONLY COMPARES TARGET SLOTS
                return targetSlotIdentifier < other.targetSlotIdentifier; 
            }

            bool operator>(const ShaderUniformPayload& other) const {
                return targetSlotIdentifier > other.targetSlotIdentifier;
            }

        private:
            bool doesTypeMatch() const{
                return value.getType() == targetSlotIdentifier.getSlotType();
            }

            void setUniformAtSlot(ShaderUniformSlot& slot); // visitor method called by Shader
            void setUniformAtLocation(shaderSlotLocation_t location);

            ShaderUniformSlotIdentifier targetSlotIdentifier;
            OpenGL_Value value;

            ShaderUniformSlotFulfillmentState fulfillmentData = {FulfillmentTimeFlag::FULFILLED_THIS_FRAME,FulfillmentLevelFlag::LEVEL_Z};
        
    };
}

#endif // SHADERUNIFORMVALUE_HPP
