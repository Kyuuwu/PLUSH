#ifndef MODELDATAREGISTRY_HPP
#define MODELDATAREGISTRY_HPP

#include "ManagedModelData.hpp"
#include "Registry.hpp"

namespace PlushGraphics {
    class ModelDataRegistry : public PlushUtil::Registry<ManagedModelData>{
    };
}

#endif // MODELDATAREGISTRY_HPP
