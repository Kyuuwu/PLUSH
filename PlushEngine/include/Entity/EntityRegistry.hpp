#ifndef ENTITYREGISTRY_HPP
#define ENTITYREGISTRY_HPP

#include "PlushEngine.hpp"
#include "Registry.hpp"
#include "ManagedEntity.hpp"
#include "EntitySpec.hpp"
#include "EntityIdentifier.hpp"

namespace PlushEngine {
    class EntityRegistry : public PlushUtil::Registry<ManagedEntity>{
        
    };
}

#endif // ENTITYREGISTRY_HPP
