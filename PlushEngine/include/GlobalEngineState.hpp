#ifndef GLOBALENGINESTATE_HPP
#define GLOBALENGINESTATE_HPP

#include "PlushEngine.hpp"
#include "Entity/EntityRegistry.hpp"

namespace PlushEngine {
    class GlobalEngineState{
        public:
            inline static EntityRegistry entityRegistry;

            static ManagedEntity getEntity(EntityIdentifier identifier){
                return entityRegistry.getItem(identifier);
            }

            static bool isEntityLoaded(EntityIdentifier identifier){
                return entityRegistry.isItemLoaded(identifier);
            }

            static EntityIdentifier loadEntity(EntitySpec spec){
                return entityRegistry.loadItem(spec);
            }

            
            static entityID_t getNextUniqueEntityID(){
                entityID_t result = nextUniqueEntityID;
                nextUniqueEntityID++;
                return result;
            }

        private:
            inline static entityID_t nextUniqueEntityID = 0;
    };
}

#endif // GLOBALENGINESTATE_HPP
