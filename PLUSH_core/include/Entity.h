#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <string>
#include <glm/glm.hpp>
#include <memory>
#include <vector>


namespace OPENGL_management{
    class Model;
    class Shader;
}

namespace PLUSH {

    class InstanceCollection;
    class Standard_Layer;

    class Instance;

    class Entity{
        public:
            std::weak_ptr<Instance> getInstance(int index = 0);
            std::weak_ptr<Instance> getInstance(std::string instanceName);

            unsigned int getNumInstances();
            std::vector<std::weak_ptr<Instance>> getInstances();

            std::weak_ptr<Instance> addInstance(std::string name, std::string modelname);

            void addInstanceToLayer(std::string instanceName, std::shared_ptr<Standard_Layer> layer, int group = 0);
            void createInstanceInLayer(std::string instanceName, std::string modelName, std::shared_ptr<Standard_Layer> layer, int group = 0);
            
            std::vector<std::shared_ptr<Instance>> instances;

        private:
    };

    std::shared_ptr<Entity> generateBasicEntity(std::string name, std::string modelname, glm::vec3 pos, glm::vec3 scale);
    std::shared_ptr<Entity> generateBasicTexturedEntity(std::string name, std::string modelname, std::string texturename, glm::vec3 pos, glm::vec3 scale);

    std::shared_ptr<Entity> generateBasicTexturedSquareEntity(std::string name, std::string texturename, glm::vec3 pos, glm::vec3 scale);

}
#endif // __ENTITY_H__