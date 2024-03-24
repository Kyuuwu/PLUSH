#include <memory>
#include <vector>


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

        private:
        std::vector<std::shared_ptr<Entity>> entities;
    };
}