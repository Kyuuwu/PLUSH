#include <memory>
#include <vector>

namespace PLUSH {
    class WindowHandler;
    class Entity_2D_Collection;
    class Entity;
}

class DiceGame{
    public:
        DiceGame();

        void run();
    
    // private:
        std::shared_ptr<PLUSH::WindowHandler> window;

        std::vector<std::shared_ptr<PLUSH::Entity>> entities;

        // std::shared_ptr<PLUSH::Entity_2D_Collection> background_entities;
        // std::shared_ptr<PLUSH::Entity_2D_Collection> mobile_entities;
        // std::shared_ptr<PLUSH::Entity_2D_Collection> foreground_entities;
};