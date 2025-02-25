#ifndef SHADERIDENTIFIER_HPP
#define SHADERIDENTIFIER_HPP

#include "PlushGraphics.hpp"

#include <string>

namespace PlushGraphics {
    class ShaderIdentifier{
        public:
            bool operator<(const ShaderIdentifier& other);

        private:
            std::string shaderName;
    };
}

#endif // SHADERIDENTIFIER_HPP
