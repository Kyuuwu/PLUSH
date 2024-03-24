#include <memory>
#include <vector>
#include <string>

namespace PLUSH{
    class Entity;

    class EntityCollection{
        public:
        EntityCollection(){};
        virtual std::vector<std::shared_ptr<Entity>> getEntitiesToRender() = 0;
        virtual void clearEntities() = 0;
    };

    class Entity_2D_Collection : public EntityCollection{
        public:
        std::vector<std::shared_ptr<Entity>> getEntitiesToRender() override;
        void clearEntities() override;

        void addEntity(std::shared_ptr<Entity> ent);

        std::shared_ptr<Entity> getEntity(std::string name);

        bool hasEntity(std::string name);
        std::shared_ptr<Entity> getLastEntitySearched();

        uint removeEntity(std::string name);

        private:
        std::vector<std::shared_ptr<Entity>> entities;

        std::shared_ptr<Entity> lastEntitySearched;
    };
}