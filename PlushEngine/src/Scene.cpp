#include "Scene.hpp"
#include "Entity/ManagedEntity.hpp"

void PlushEngine::Scene::runLogicUpdate() {
    for(ManagedEntity entity : entities){
        entity.runLogicUpdate();
    }
}
