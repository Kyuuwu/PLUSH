#ifndef MODELINSTANCEREGISTRY_HPP
#define MODELINSTANCEREGISTRY_HPP

#include "ManagedModelInstance.hpp"
#include "Registry.hpp"

namespace PlushGraphics {
    class ModelInstanceRegistry : public PlushUtil::Registry<ManagedModelInstance>{
    };
}

#endif // MODELINSTANCEREGISTRY_HPP
