#include "../include/Entity/Entity.hpp"
#include "PlushEngine.hpp"
#include "EntityOperator.hpp"

PlushEngine::Entity::Entity(EntitySpec spec):
identifier()
{
    
}

void PlushEngine::Entity::_runLogicUpdate() {
    for(size_t i = 0; i < operators.size(); i++){
        operators[i]->runLogicUpdate();
    }
}
