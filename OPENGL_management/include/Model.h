#include <vector>
#include <memory>

#include "ShaderUniforms.h"

namespace OPENGL_management {
    class Shader;

    class Texture2D;

    class Model{
        public:
            Model(std::string name, unsigned int vao, unsigned int vbo, unsigned int num_vx, std::vector<ShaderInput> inputs);
            Model(std::string name, unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int num_vx,  std::vector<ShaderInput> inputs);

            bool checkInputCompatibility(Shader* shader);

            void drawWithShader(Shader* shader, std::vector<ShaderUniform> external_uniforms = std::vector<ShaderUniform>(), bool resetSetChecks = true, std::vector<TextureNamePair> external_textures = std::vector<TextureNamePair>());

            void newDrawWithShader(std::shared_ptr<Shader> shader);

            void addInternalUniform(ShaderUniform uniform);
            void setInternalUniforms(std::vector<ShaderUniform> uniforms);

            std::vector<ShaderUniform> getInternalUniforms();

            // std::vector<std::shared_ptr<Texture2D>> getTextures2D(); // BAD DONT USE
            void setTextures2D(std::vector<std::shared_ptr<Texture2D>> textures); // BAD DONT USE
            void setTexture2DUniform(std::string uniformname, std::string texturename); // BAD DONT USE

            std::vector<TextureNamePair> getTextures2D();
            void setTextures2D(std::vector<TextureNamePair> textures = std::vector<TextureNamePair>());
            void addTexture2D(TextureNamePair texture);
            void addTexture2D(std::string uniformname, std::string texturename);

            std::string getName();

            void useDefaultTexture2D(Shader* shader, std::string uniformname);
            void setDefaultTexture(std::string newDefaultTexture);

        protected:
            void useTexture2D(Shader* shader, TextureNamePair texture, unsigned int texture_unit);

            void draw();

            std::string name;

            std::vector<std::shared_ptr<Texture2D>> textures_2D; // BAD DONT USE

            std::vector<TextureNamePair> texture2D_name_pairs; // BAD DONT USE

            std::string defaultTextureName;

            std::vector<ShaderInput> vertex_inputs;

            std::vector<ShaderUniform> internal_uniforms;
            std::vector<ShaderUniform> texture_uniforms;

            unsigned int number_of_vertices = 0;

            unsigned int VAO = 0;

            unsigned int VBO = 0;

            unsigned int EBO = 0;
            bool usingEBO = false;
    };
}