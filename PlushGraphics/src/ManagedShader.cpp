#include "../include/Shader/ManagedShader.hpp"
#include "UniformResolver.hpp"

void PlushGraphics::ManagedShader::acceptUniformResolver(WeakPtrUniformResolver resolver) {
    resolver.lock()->resolveUniformRequirements(this->clone());
}
