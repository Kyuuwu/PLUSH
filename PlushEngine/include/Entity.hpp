#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "EntityStatus.hpp"
#include "PlushEngine.hpp"
#include <vector>

namespace PlushEngine {
    class Entity{
        public:
            friend class EntityOperator;
            
            void runLogicUpdate(); 

        private:
            EntityStatus status;

            std::vector<UniquePtrEntityOperator> operators;
    };
}

#endif // ENTITY_HPP
