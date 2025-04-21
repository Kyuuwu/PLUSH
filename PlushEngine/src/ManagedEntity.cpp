#include "Entity/ManagedEntity.hpp"
#include "EngineInterfaces/BaseEntityMod.hpp"
#include "GlobalEngineState.hpp"

namespace PlushEngine {
    ManagedEntity::ManagedEntity() // create a new empty entity through registry and delegate constructor to copy
        : ManagedEntity(PlushEngine::GlobalEngineState::getEntity(PlushEngine::GlobalEngineState::loadEntity(PlushEngine::EntitySpec())))
    {}

    ManagedEntity& ManagedEntity::addEntityMod(SharedPtrEntityMod mod) {
        (*this)->_addEntityMod(mod);
        
        mod->setOwningEntity(*this);
    
        return *this;
    }
}

