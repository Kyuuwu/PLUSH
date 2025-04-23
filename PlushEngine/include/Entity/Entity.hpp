#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "EntityStatus.hpp"
#include "PlushEngine.hpp"
#include "EntityIdentifier.hpp"
#include "Shader/ManagedShader.hpp"
#include <vector>

namespace PlushEngine {
    class Entity{
        public:
            friend class EntityMod;
            using Spec = EntitySpec;
            using Identifier = EntityIdentifier;

            Entity(EntitySpec spec);
            
            void _addEntityMod(SharedPtrEntityMod mod){
                mods.push_back(mod);
            }

            void _runLogicUpdateOnAllMods(); 
            void _runPredrawTasksOnAllMods();
            void _resolveUniformRequirementsWithAllMods(PlushGraphics::ManagedShader shader);

            std::vector<SharedPtrEntityMod> _getEntityMods(){
                return mods;
            }

            EntityIdentifier getIdentifier() const { return identifier; }
            EntityStatus& _status(){return status;}

        private:
            EntityIdentifier identifier;

            EntityStatus status;

            std::vector<SharedPtrEntityMod> mods;
    };
}

#endif // ENTITY_HPP
