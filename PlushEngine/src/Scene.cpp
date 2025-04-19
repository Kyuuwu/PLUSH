#include "../include/Scene/Scene.hpp"
#include "GraphicsLayer/ManagedGraphicsLayer.hpp"
#include "Scene/SceneSpec.hpp"
#include "Entity/ManagedEntity.hpp"
#include "Window/ManagedWindow.hpp"

namespace PlushEngine {
    Scene::Scene(SceneSpec spec)
    {
        #pragma unused (spec)
    }

    void Scene::_runLogicUpdate() {
        for(ManagedEntity entity : entities){
            entity.runLogicUpdateOnAllMods();
        }
    }

    void Scene::_loadOntoWindow(PlushGraphics::ManagedWindow window) {
        window.clearGraphicsLayers();

        for(PlushGraphics::ManagedGraphicsLayer layer : graphicsLayers){
            window.addGraphicsLayer(layer);
        }
    }
}
