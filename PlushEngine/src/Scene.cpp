#include "../include/Scene/Scene.hpp"
#include "Scene/SceneSpec.hpp"
#include "Entity/ManagedEntity.hpp"

namespace PlushEngine {
    Scene::Scene(SceneSpec spec)
    {
        #pragma unused (spec)
    }

    void Scene::runLogicUpdate() {
        for(ManagedEntity entity : entities){
            entity.runLogicUpdateOnAllOperators();
        }
    }
}
