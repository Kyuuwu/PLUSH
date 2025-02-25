#ifndef SHADERUNIFORMSLOTIDENTIFIER_HPP
#define SHADERUNIFORMSLOTIDENTIFIER_HPP

#include "PlushGraphics.hpp"
#include <string>

namespace PlushGraphics {
    class ShaderMetadata::ShaderUniformSlotIdentifier{
        public:
            bool operator<(const ShaderUniformSlotIdentifier& other) const { return slotName < other.slotName;}
        
            std::string getSlotName() const { return slotName; }
            OpenGL_Type getSlotType() const { return slotType; }

        private:
            std::string slotName;
            OpenGL_Type slotType;
    };
}

#endif // SHADERUNIFORMSLOTIDENTIFIER_HPP
