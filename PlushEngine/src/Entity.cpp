#include "Entity.hpp"
#include "PlushEngine.hpp"
#include "EntityOperator.hpp"

void PlushEngine::Entity::runLogicUpdate() {
    for(size_t i = 0; i < operators.size(); i++){
        operators[i]->runLogicUpdate();
    }
}
