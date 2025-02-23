#ifndef PLUSH_GRAPHICS_HPP
#define PLUSH_GRAPHICS_HPP

namespace PlushGraphics {
    enum class Exception;

    enum class OpenGL_Type;

    class WindowBuilder; // holds data/settings/dimensions for building windows
    class Window; // Manages a window

    class GraphicsLayer; // Layer to draw drawables onto within Window
    class Drawable; // Previously Instance, the drawable data, incl. model, that a game-engine-level entity needs 

    class ShaderIdentifier; 
    class Shader; // container for a compiled shader
    class ShaderLibrary; // holds all compiled shaders needed

    namespace ShaderMetadata {
        class ShaderInputValue;
        class ShaderInputSlotIdentifier;

        class ShaderInputSlot;

        class ShaderUniformValue; // holds uniform value and metadata
        class ShaderUniformSlotIdentifier; // holds metadata for which slot uniform values are targeted to

        class ShaderUniformSlot; // holds metadata for uniforms taken by a shader
    }

    namespace VertexData {
        class Vertex;
    }

    class Texture2D;
    class TextureLibrary; // holds all textures

    class ModelIdentifier; // identifier struct for a given model
    class ModelData; // contains all vertex data for a given model, possibly containing data for multiple shader input formats
    class ModelInstance; // contains vertex data for a given model matched to the inputs of exactly one shader

    namespace ModelInstanceMetadata {
        class ModelInstanceMetadata; // contains metadata and compat checking for the originating shader & modeldata of a modelinstance
    }

    class ModelLibrary; // holds modeldata (and possible modelinstances)
}

#endif // PLUSH_GRAPHICS_HPP
