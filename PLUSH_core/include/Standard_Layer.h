#ifndef __STANDARD_LAYER_H__
#define __STANDARD_LAYER_H__

#include <memory>
#include <vector>

#include "ShaderUniforms.h"

namespace OPENGL_management{
    class Shader;
}

namespace PLUSH {
    class Instance;
    class InstanceCollection;

    class Standard_Layer{
        public:
            void draw(std::vector<OPENGL_management::ShaderUniform> external_uniforms = std::vector<OPENGL_management::ShaderUniform>());

            void setLayerDimensions(float x, float y);
            void setLayerHalfDimensions(float x, float y);

            void setLayerPositionCOM(float x, float y);

            void addInstance(std::weak_ptr<Instance> newInstance, int group = -1);

            void setName(std::string newName);
            std::string getName();

        private:
            std::shared_ptr<OPENGL_management::Shader> defaultShader;
            std::vector<std::shared_ptr<OPENGL_management::Shader>> alternativeShaders;

            std::shared_ptr<InstanceCollection> collection;

            std::string name = "CHANGE_THIS";

            glm::vec2 layer_position_COM = glm::vec2(0.0f, 0.0f);
            glm::vec2 layer_halfdimensions = glm::vec2(0.4f, 0.4f);
            glm::vec2 layer_internal_shift = glm::vec2(0.0f, 0.0f);


            std::vector<OPENGL_management::ShaderUniform> uniforms;
            bool uniforms_up_to_date = false;
            virtual void generateUniforms();
    };
}

#endif // __STANDARD_LAYER_H__