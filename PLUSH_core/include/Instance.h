#ifndef __INSTANCE_H__
#define __INSTANCE_H__

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

    class Entity;
    class InstanceCollection;
    class Standard_Layer;

    class Instance{
        public:
            Instance(std::string name, std::shared_ptr<OPENGL_management::Model> model, InstanceStatus status = InstanceStatus());
            Instance(std::string name, std::string modelname, InstanceStatus status = InstanceStatus());

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

            int32_t getLayerOrder() const;
            void setLayerOrder(int32_t new_layerorder);

            static bool compareLayerOrder(const Instance& a, const Instance& b);
            static bool compareLayerOrderShared(const std::shared_ptr<Instance>& a, const std::shared_ptr<Instance>& b);
            static bool compareLayerOrderWeak(const std::weak_ptr<Instance>& a, const std::weak_ptr<Instance>& b);

            glm::vec3 getScale();
            void setScale(glm::vec3 newScale);

            void drawWithShader(OPENGL_management::Shader* shader, std::vector<OPENGL_management::ShaderUniform> external_uniforms = std::vector<OPENGL_management::ShaderUniform>(), bool resetPerInstanceChecks = true);
            void newDrawWithShader(std::shared_ptr<OPENGL_management::Shader> shader);

            std::shared_ptr<Instance> copy();

            InstanceStatus getStatus();
            InstanceStatus* getStatusPointer();
            void setStatus(InstanceStatus newstatus);

            void setParentEntity(std::shared_ptr<Entity> parent); // MOVE TO A CONSTRUCTOR REQUIREMENT AFTER REVAMP
            std::shared_ptr<Entity> getParentEntity();

            void addContainingCollection(std::weak_ptr<InstanceCollection> collection);

            OPENGL_management::Pair_Unfulfilled_Overriden_UniformTarget fulfillShaderRequirements( 
                std::shared_ptr<OPENGL_management::Shader> shader,
                std::vector<OPENGL_management::ShaderUniformTarget> unfulfilledTargets,
                std::vector<OPENGL_management::ShaderUniformTarget> fulfilledTargets);

        private:
            void generateModelMatrixIfNeeded();
            void generateModelMatrix();

            std::vector<OPENGL_management::ShaderUniform> uniforms;

            std::vector<OPENGL_management::ShaderUniform> internal_uniforms;
            // std::vector<OPENGL_management::ShaderUniform> texture_uniforms; // BAD DONT USE

            std::vector<OPENGL_management::TextureNamePair> texture2D_name_pairs;

            std::string name;

            std::shared_ptr<OPENGL_management::Model> model;

            std::weak_ptr<Entity> parentEntity;

            std::vector<std::weak_ptr<InstanceCollection>> containingCollections;

            glm::vec3 position = glm::vec3(0.0f);
            bool positionUpdated = true;

            glm::vec3 scale = glm::vec3(1.0f);
            std::shared_ptr<RotationHandler> rotation;
            
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            bool scaleUpdated = true;

            int32_t layerOrder = 0;

            InstanceStatus status;

            bool tryToFulfillUniform(std::shared_ptr<OPENGL_management::Shader> shader, OPENGL_management::ShaderUniformTarget target);
    };
}
#endif // __INSTANCE_H__