#include "Entity/ManagedEntity.hpp"
#include "EngineInterfaces/BaseEntityMod.hpp"

namespace PlushEngine {
    ManagedEntity& ManagedEntity::addEntityMod(SharedPtrEntityMod mod) {
        (*this)->_addEntityMod(mod);
        
        mod->setOwningEntity(*this);
    
        return *this;
    }
}

