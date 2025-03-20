#ifndef PLUSH_GRAPHICS_HPP
#define PLUSH_GRAPHICS_HPP

#include <cstdint>
#include <memory>
#include <sys/types.h>

namespace PlushGraphics {
    using shaderSlotLocation_t = uint32_t;
    using shaderObjectReferenceID = uint32_t;
    using bufferReferenceID = uint32_t;
    using textureReferenceID = uint32_t;
    
    using drawableID_t = uint32_t;
    using graphicsLayerID_t = uint32_t;

    enum class PlushGraphicsException;

    enum class OpenGL_Type;
    class OpenGL_Value;

    class GlobalGraphicsState; // manages initialization and closing out of program, and all global registries

    class WindowSpec; // holds data/settings/dimensions for building windows
    class Window; // OpenGL window class
    class WindowIdentifier;
    class ManagedWindow;
    class WindowRegistry;
    class WindowSettings; // struct to hold all window settings, such as name and sizes

    class UniformResolver; // interface for fulfilling uniform requirements of drawing ModelInstances
    typedef std::shared_ptr<UniformResolver> SharedPtrUniformResolver;
    typedef std::weak_ptr<UniformResolver> WeakPtrUniformResolver;
    typedef std::unique_ptr<UniformResolver> UniquePtrUniformResolver;

    template<typename T>
    concept UniResDerived =
        requires {
            requires std::derived_from<T, UniformResolver>;
        };

    namespace UniformResolvers {
        class NoOpResolver; // UniformResolver which makes no attempt to resolve uniforms, or do anything else
        class PreloadedUniformsResolver; // UniformResolver which attempts to resolve uniforms using a provided list
    }

    class ManagedGraphicsLayer;
    class GraphicsLayerIdentifier;
    class GraphicsLayer; // Layer to draw drawables onto within Window
    class GraphicsLayerSpec;
    class GraphicsLayerRegistry;

    class ManagedDrawable;
    class DrawableIdentifier;
    class DrawableSpec;
    class Drawable; // Previously Instance, the drawable data, incl. model, that a game-engine-level entity needs 
    class DrawableRegistry;

    class ShaderSpec; // specification for loading a shader
    class ShaderIdentifier; // identifier for retrieving a compiled shader
    class Shader; // container for a compiled shader
    class ShaderRegistry; // holds all compiled shaders needed
    class ManagedShader; // wrapper for smart pointer to shaders, inherits ManagedObject interface from PlushUtil

    class ShaderMemento;

    namespace ShaderMetadata {
        class ShaderInputValue;
        class ShaderInputSlotIdentifier;

        class ShaderInputSlot;

        class ShaderUniformPayload; // holds uniform value and metadata
        class ShaderUniformSlotIdentifier; // holds metadata for which slot uniform values are targeted to

        enum class FulfillmentTimeFlag;
        enum class FulfillmentLevelFlag;
        class ShaderUniformSlotFulfillmentState; // stores information about what kinds of objects have fulfilled a slot, and when
        class ShaderUniformSlot; // holds metadata for uniforms taken by a shader
    }

    class ModelVertex;

    class Texture2DRegistry; // holds all textures
    class Texture2D;
    class ManagedTexture2D; // wrapper for smart pointer to textures, inherits ManagedObject interface from PlushUtil
    class Texture2DSpec;
    class Texture2DIdentifier;

    class ModelDataSpec; // specification for loading ModelData from a file
    class ModelDataIdentifier; // identifier struct for a given model
    class ModelData; // contains all vertex data for a given model, possibly containing data for multiple shader input formats
    class ModelDataRegistry; // holds ModelData items
    class ManagedModelData; // wrapper for smart pointer to ModelData, inherits ManagedObject interface from PlushUtil

    class ModelInstanceSpec; // spec for creating a ModelInstance from a ModelData and a Shader
    class ModelInstanceIdentifier; // identifies a ModelInstance
    class ModelInstance; // contains vertex data for a given model matched to the inputs of exactly one shader
    class ModelInstanceRegistry; // holds ModelInstance items within a ModelData
    class ManagedModelInstance; // wrapper for smart pointer to ModelInstance, inherits ManagedObject interface from PlushUtil

    namespace ModelInstanceMetadata {
        class ModelInstanceMetadata; // contains metadata and compat checking for the originating shader & modeldata of a modelinstance
    }
}

#endif // PLUSH_GRAPHICS_HPP
