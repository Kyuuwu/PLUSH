#ifndef SHADERIDENTIFIER_HPP
#define SHADERIDENTIFIER_HPP

#include "PlushGraphics.hpp"

#include <string>

namespace PlushGraphics {
    class ShaderIdentifier{
        public:
            ShaderIdentifier(std::string name) : shaderName(name){}
            bool operator<(const ShaderIdentifier& other);

            std::string getShaderName() const { return shaderName; }

        private:
            std::string shaderName;
    };
}

#endif // SHADERIDENTIFIER_HPP
