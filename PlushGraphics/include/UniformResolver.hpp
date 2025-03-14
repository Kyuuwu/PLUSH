#ifndef UNIFORMRESOLVER_HPP
#define UNIFORMRESOLVER_HPP

#include "PlushGraphics.hpp"

namespace PlushGraphics {
    class UniformResolver{
        public:
            UniformResolver(){}
            virtual ~UniformResolver(){}

            virtual void resolveUniformRequirements(ManagedShader shader) = 0;
    };
}

#endif // UNIFORMRESOLVER_HPP
