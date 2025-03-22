#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../EntityStatus.hpp"
#include "PlushEngine.hpp"
#include "EntityIdentifier.hpp"
#include <vector>

namespace PlushEngine {
    class Entity{
        public:
            friend class EntityOperator;
            using Spec = EntitySpec;
            using Identifier = EntityIdentifier;

            Entity(EntitySpec spec);
            
            void _runLogicUpdate(); 

            EntityIdentifier getIdentifier() const { return identifier; }

        private:
            EntityIdentifier identifier;

            EntityStatus status;

            std::vector<UniquePtrEntityOperator> operators;
    };
}

#endif // ENTITY_HPP
