#include "PLUSH_core_includes.h"

#include "OPENGL_management_includes.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Helpers.h"

#include <iostream>

namespace PLUSH {


    std::shared_ptr<Entity> generateBasicEntity(std::string name, std::string modelname, glm::vec3 pos, glm::vec3 scale){
        
        std::shared_ptr<Entity> entity(new Entity());
        entity->addInstance("Default", modelname);
        std::shared_ptr<Instance> inst = entity->getInstance("Default").lock();
        
        inst->getStatusPointer()->visible=true;
        inst->setScale(scale);
        inst->setPosition(pos);    

        return entity;
    }
    
    std::shared_ptr<Entity> generateBasicTexturedEntity(std::string name, std::string modelname, std::string texturename, glm::vec3 pos, glm::vec3 scale){
        
        std::shared_ptr<Entity> ent =  generateBasicEntity(name, modelname, pos, scale);

        ent->getInstance("Default").lock()->setTexture2DUniform("primaryTexture", texturename);

        return ent;
    }

    std::shared_ptr<Entity> generateBasicTexturedSquareEntity(std::string name, std::string texturename, glm::vec3 pos, glm::vec3 scale){
        return generateBasicTexturedEntity(name, "square2D.vx", texturename, pos, scale);
    }
    
    std::weak_ptr<Instance> Entity::getInstance(int index)
    {
        return instances[index];
    }
    
    std::weak_ptr<Instance> Entity::getInstance(std::string instanceName)
    {
        for (std::shared_ptr<Instance> inst : instances){
            if (inst->getName() == instanceName){
                return inst;
            }
        }
        throw(INSTANCE_NOT_FOUND);
    }
    
    std::shared_ptr<Instance> Entity::getInstanceAsSharedPtr(int index)
    {
        return getInstance(index).lock();
    }
    
    std::shared_ptr<Instance> Entity::getInstanceAsSharedPtr(std::string instanceName)
    {
        return getInstance(instanceName).lock();
    }
    
    unsigned int Entity::getNumInstances()
    {
        return instances.size();
    }
    
    std::vector<std::weak_ptr<Instance>> Entity::getInstances()
    {
        std::vector<std::weak_ptr<Instance>> weak_instances;

        for (std::shared_ptr<Instance> inst: instances){
            weak_instances.push_back(inst);
        }

        return weak_instances;
    }
    
    std::weak_ptr<Instance> Entity::addInstance(std::string name, std::string modelname)
    {
        std::shared_ptr<Instance> newInstance(new Instance(name, modelname));
        instances.push_back(newInstance);
        return newInstance;
    }
    
    void Entity::addInstanceToLayer(std::string instanceName, std::shared_ptr<Standard_Layer> layer, int group)
    {
        layer->addInstance(getInstance(instanceName), group);
    }
    
    void Entity::createInstanceInLayer(std::string instanceName, std::string modelName, std::shared_ptr<Standard_Layer> layer, int group)
    {
        layer->addInstance(addInstance(instanceName, modelName));
    }
    
}