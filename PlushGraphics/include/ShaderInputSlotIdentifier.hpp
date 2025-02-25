#ifndef SHADERINPUTSLOTIDENTIFIER_HPP
#define SHADERINPUTSLOTIDENTIFIER_HPP

#include "PlushGraphics.hpp"
#include <string>

namespace PlushGraphics {
    class ShaderMetadata::ShaderInputSlotIdentifier{
        public:
        std::string getSlotName() const { return slotName; }
        OpenGL_Type getSlotType() const { return slotType; }
            
        private:
            std::string slotName;
            OpenGL_Type slotType;
    };
}

#endif // SHADERINPUTSLOTIDENTIFIER_HPP
