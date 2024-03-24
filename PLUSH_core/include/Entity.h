#include <string>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "EntityStatus.h"
#include "ShaderUniforms.h"

namespace OPENGL_management{
    class Model;
    class Shader;
}

namespace PLUSH {
    class RotationHandler;

    class Entity{
        public:
            Entity(std::string name, std::shared_ptr<OPENGL_management::Model> model, EntityStatus status = EntityStatus());
            Entity(std::string name, std::string modelname, EntityStatus status = EntityStatus());

            std::string getName();

            void addInternalUniform(OPENGL_management::ShaderUniform uniform);
            void setInternalUniforms(std::vector<OPENGL_management::ShaderUniform> uniforms);

            std::vector<OPENGL_management::ShaderUniform> getInternalUniforms();
            void setTexture2DUniform(std::string uniformname, std::string texturename);

            glm::mat4 getModelMatrix();

            std::shared_ptr<RotationHandler> getRotationHandler();
            void setRotationHandler(std::shared_ptr<RotationHandler> rotationHandler);

            glm::vec3 getPosition();
            void setPosition(glm::vec3 newPosition);

            glm::vec3 getScale();
            void setScale(glm::vec3 newScale);

            void drawWithShader(OPENGL_management::Shader* shader, std::vector<OPENGL_management::ShaderUniform> external_uniforms = std::vector<OPENGL_management::ShaderUniform>(), bool resetChecks = true);

            std::shared_ptr<Entity> copy();

            EntityStatus getStatus();
            EntityStatus* getStatusPointer();
            void setStatus(EntityStatus newstatus);

        private:
            void generateModelMatrixIfNeeded();
            void generateModelMatrix();

            std::vector<OPENGL_management::ShaderUniform> internal_uniforms;
            // std::vector<OPENGL_management::ShaderUniform> texture_uniforms; // BAD DONT USE

            std::vector<OPENGL_management::TextureNamePair> texture2D_name_pairs;

            std::string name;

            std::shared_ptr<OPENGL_management::Model> model;

            glm::vec3 position = glm::vec3(0.0f);
            bool positionUpdated = true;

            glm::vec3 scale = glm::vec3(1.0f);
            std::shared_ptr<RotationHandler> rotation;
            
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            bool scaleUpdated = true;

            EntityStatus status;
    };

    std::shared_ptr<Entity> generateBasicEntity(std::string name, std::string modelname, glm::vec3 pos, glm::vec3 scale);
    std::shared_ptr<Entity> generateBasicTexturedEntity(std::string name, std::string modelname, std::string texturename, glm::vec3 pos, glm::vec3 scale);
    std::shared_ptr<Entity> generateBasicTexturedSquareEntity(std::string name, std::string texturename, glm::vec3 pos, glm::vec3 scale);
}