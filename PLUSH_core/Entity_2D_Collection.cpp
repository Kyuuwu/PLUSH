#include "PLUSH_core_includes.h"
#include "PLUSH_core_Exceptions.h"

namespace PLUSH {
    std::vector<std::shared_ptr<Instance>> Entity_2D_Collection::getEntitiesToRender(){
        return entities;
    }

    void Entity_2D_Collection::clearEntities(){
        entities = std::vector<std::shared_ptr<Instance>>();
    }

    void Entity_2D_Collection::addEntity(std::shared_ptr<Instance> ent){
        entities.push_back(ent);
    }

    std::shared_ptr<Instance> Entity_2D_Collection::getEntity(std::string name){
        for(std::shared_ptr<Instance> ent : entities){
            if (ent->getName() == name){
                return ent;
            }
        }
        throw(ENTITY_NOT_FOUND);
    }

    bool Entity_2D_Collection::hasEntity(std::string name){
        for(std::shared_ptr<Instance> ent : entities){
            if (ent->getName() == name){
                lastEntitySearched = ent;
                return true;
            }
        }
        return false;
    }

    std::shared_ptr<Instance> Entity_2D_Collection::getLastEntitySearched(){
        return lastEntitySearched;
    }

    uint Entity_2D_Collection::removeEntity(std::string name){
        uint num_deleted = 0;

        for(int i = entities.size()-1; i >= 0; i--){
            if (entities.at(i)->getName() == name){
                entities.erase(entities.begin() + i);
                num_deleted++;
            }
        }
        return num_deleted;
    }
}