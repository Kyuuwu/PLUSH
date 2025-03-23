#include "../include/Entity/Entity.hpp"
#include "PlushEngine.hpp"
#include "../include/BaseEntityMod.hpp"

PlushEngine::Entity::Entity(EntitySpec spec):
identifier()
{
    #pragma unused(spec)
}

void PlushEngine::Entity::_runLogicUpdateOnAllOperators() {
    for(size_t i = 0; i < operators.size(); i++){
        operators[i]->runLogicUpdate();
    }
}
