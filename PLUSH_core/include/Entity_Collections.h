#include <memory>
#include <vector>
#include <string>

namespace PLUSH{
    class Instance;

    class EntityCollection{
        public:
        EntityCollection(){};
        virtual std::vector<std::shared_ptr<Instance>> getEntitiesToRender() = 0;
        virtual void clearEntities() = 0;
    };

    class Entity_2D_Collection : public EntityCollection{
        public:
        std::vector<std::shared_ptr<Instance>> getEntitiesToRender() override;
        void clearEntities() override;

        void addEntity(std::shared_ptr<Instance> ent);

        std::shared_ptr<Instance> getEntity(std::string name);

        bool hasEntity(std::string name);
        std::shared_ptr<Instance> getLastEntitySearched();

        uint removeEntity(std::string name);

        private:
        std::vector<std::shared_ptr<Instance>> entities;

        std::shared_ptr<Instance> lastEntitySearched;
    };
}