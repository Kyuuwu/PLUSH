#include "../include/Entity/Entity.hpp"
#include "PlushEngine.hpp"
#include "../include/EngineInterfaces/BaseEntityMod.hpp"

PlushEngine::Entity::Entity(EntitySpec spec):
identifier()
{
    #pragma unused(spec)
}

void PlushEngine::Entity::_runLogicUpdateOnAllMods() {
    for(size_t i = 0; i < mods.size(); i++){
        mods[i]->runLogicUpdate();
    }
}

void PlushEngine::Entity::_runPredrawTasksOnAllMods() {
    for(auto mod : mods){
        mod->runPredrawTasks();
    }
}

void PlushEngine::Entity::_resolveUniformRequirementsWithAllMods(PlushGraphics::ManagedShader shader) {
    for(auto op : mods){
        op->resolveUniformRequirements(shader);
    }
}
