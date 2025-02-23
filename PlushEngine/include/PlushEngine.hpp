#ifndef PLUSHENGINE_HPP
#define PLUSHENGINE_HPP

namespace PlushEngine {
    class WindowHandle;

    class Entity; // game engine level abstraction of a object in engine space
    class EntityStatus; // stores all necessary data about the state of an entity (expandable/modular)

    class EntityOperator; // implements functionality allowing an entity to manage its drawables (physics, effects, etc)

    namespace EntityOperators { // inheritance as interface
        // classes inheriting from EntityOperator, implementing individual functions
        // modular operators can be individually loaded into an entity to implement specific behavior
    }

    class Scene; // manages the layers, shaders, and entities of the current game state

    class Camera; // manages the type and details of what arrives on screen

    class UpdateClock; // tracks timers for frame updates, and various logic updates, which may have different rates etc
}

#endif // PLUSHENGINE_HPP
