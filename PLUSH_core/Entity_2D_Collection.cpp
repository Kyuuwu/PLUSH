#include "Entity_Collections.h"

namespace PLUSH {
    std::vector<std::shared_ptr<Entity>> Entity_2D_Collection::getEntitiesToRender(){
        return entities;
    }

    void Entity_2D_Collection::clearEntities(){
        entities = std::vector<std::shared_ptr<Entity>>();
    }

    void Entity_2D_Collection::addEntity(std::shared_ptr<Entity> ent){
        entities.push_back(ent);
    }
}