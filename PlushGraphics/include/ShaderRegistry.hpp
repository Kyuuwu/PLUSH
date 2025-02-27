#ifndef SHADERREGISTRY_HPP
#define SHADERREGISTRY_HPP

#include "ManagedShader.hpp"
#include "Registry.hpp"

namespace PlushGraphics {
    class ShaderRegistry : public PlushUtil::Registry<ManagedShader>{
    };
}

#endif // SHADERREGISTRY_HPP
