#ifndef PLUSHENGINE_HPP
#define PLUSHENGINE_HPP

#include <memory>

namespace PlushEngine {
    using entityID_t = size_t;
    using sceneID_t = size_t;

    class GlobalEngineState;
    // may want World class and/or handle reloading assets in global states 


    class WindowHandle; // may not be necessary

    class EntityIdentifier;
    class EntitySpec;
    class ManagedEntity;
    class Entity; // game engine level abstraction of a object in engine space
    class EntityRegistry;

    class EntityStatus; // stores all necessary data about the state of an entity (expandable/modular)

    namespace DataStructures {
        class Position2D;
        class Position3D;
        class Rotation2D;
        class Rotation3D;

        /// Stores position and rotation in two dimensions.
        class CoordinateState2D;
        /// Stores position and rotation in three dimensions. TBD
        class CoordinateState3D;
    }

    namespace EngineInterfaces{
        /// implements functionality allowing an `Entity` to manage its drawables (physics, effects, etc)
        class BaseEntityMod; 
        /// Interface that allows receiving a command
        class Commandable;
        /// Command interface
        class Command;
        
        /// Interface to control a Drawable (move between layers, toggle vis, change modelinst, etc)
        class ControlsDrawable;
        /// Interface to control the coordinate state of an entity in 2D
        class ControlsCoordinateState2D;
        /// Interface to control the coordinate state of an entity in 3D
        class ControlsCoordinateState3D;
    }

    template<typename T>
    concept ModDerived =
        requires {
            requires std::derived_from<T, EngineInterfaces::BaseEntityMod>;
        };

    typedef std::shared_ptr<EngineInterfaces::BaseEntityMod> SharedPtrEntityMod;
    typedef std::weak_ptr<EngineInterfaces::BaseEntityMod> WeakPtrEntityMod;
    typedef std::unique_ptr<EngineInterfaces::BaseEntityMod> UniquePtrEntityMod;

    namespace EntityMods { // inheritance as interface
        // classes inheriting from EntityOperator, implementing individual functions
        // modular operators can be individually loaded into an entity to implement specific behavior
        class DrawMod;

        class ResolverMod;

        /// simple control of position and rotation in 2D
        class Placement2DMod;
    }

    namespace Commands {
        /// A no-op command
        class NoOpCommand;

        class SetAngleCommand;
    
    }

    class CommandTargetFilter;
    typedef std::unique_ptr<CommandTargetFilter> UniquePtrFilter;
    typedef std::shared_ptr<CommandTargetFilter> SharedPtrFilter;
    namespace CommandTargetFilters {
        /// Filters by the exact (most-derived) class that a Mod was instantiated as
        class TypeFilter;

        /// Filters by whether a Mod can be dynamic_cast to the templated class
        template<typename TargetClass>
        class DynamicCastFilter;
    }

    namespace EngineUniformResolvers {
        class EntityUniformResolver;
    }

    // should be managed
    class Scene; // manages the layers, shaders, and entities of the current game state
    class SceneSpec;
    class SceneIdentifier;
    class ManagedScene;
    class SceneRegistry;

    class Camera; // manages the type and details of what arrives on screen

    class UpdateClock; // tracks timers for frame updates, and various logic updates, which may have different rates etc
}

#endif // PLUSHENGINE_HPP
