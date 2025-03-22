#ifndef ENTITYREGISTRY_HPP
#define ENTITYREGISTRY_HPP

#include "Registry.hpp"
#include "ManagedEntity.hpp"

namespace PlushEngine {
    class EntityRegistry : public PlushUtil::Registry<ManagedEntity>{
        
    };
}

#endif // ENTITYREGISTRY_HPP
