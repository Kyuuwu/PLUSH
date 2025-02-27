#include "ModelInstance.hpp"
#include "ModelInstanceIdentifier.hpp"
#include "ModelInstanceSpec.hpp"
#include "ManagedShader.hpp"
#include "ManagedModelData.hpp"

PlushGraphics::ModelInstance::ModelInstance(ModelInstanceSpec spec)
    : identifier(spec)
{
    // problem: registries not global/singleton/static
}

