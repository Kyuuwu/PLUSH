#ifndef SHADERINPUTSLOTIDENTIFIER_HPP
#define SHADERINPUTSLOTIDENTIFIER_HPP

#include "PlushGraphics.hpp"
#include <string>

namespace PlushGraphics {
    class ShaderMetadata::ShaderInputSlotIdentifier{
        public:
            ShaderInputSlotIdentifier(std::string _slotName, OpenGL_Type _slotType)
            : slotName(_slotName), slotType(_slotType) {}

            bool operator==(const ShaderInputSlotIdentifier& other) const{
                return (slotName == other.slotName) && (slotType == other.slotType);
            }

            std::string getSlotName() const { return slotName; }
            OpenGL_Type getSlotType() const { return slotType; }
            
        private:
            std::string slotName;
            OpenGL_Type slotType;
    };
}

#endif // SHADERINPUTSLOTIDENTIFIER_HPP
