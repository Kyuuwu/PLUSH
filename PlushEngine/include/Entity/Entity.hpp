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
            
            void _addOperator(SharedPtrEntityMod op){
                operators.push_back(op);
            }

            void _runLogicUpdateOnAllOperators(); 
            void _runPredrawTasksOnAllOperators();
            void _resolveUniformRequirementsWithAllOperators(PlushGraphics::ManagedShader shader);

            EntityIdentifier getIdentifier() const { return identifier; }

        private:
            EntityIdentifier identifier;

            EntityStatus status;

            std::vector<SharedPtrEntityMod> operators;
    };
}

#endif // ENTITY_HPP
