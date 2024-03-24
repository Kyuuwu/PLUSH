#include <memory>

#include "ShaderUniforms.h"
#include "Drawable.h"

#include <glm/glm.hpp>

namespace OPENGL_management{
    class Shader;
}

namespace PLUSH{
    class Entity;
    class EntityCollection;

    class Entity_2D_Animated_Layer : public DrawableLayer{
        public:
        Entity_2D_Animated_Layer(std::string name = "Default_2d_layer_name:FIX_THIS");
        
        void draw(std::vector<OPENGL_management::ShaderUniform> external_uniforms = std::vector<OPENGL_management::ShaderUniform>()) override;

        void setEntityCollection(std::shared_ptr<EntityCollection> collection);

        void setLayerDimensions(float x, float y);
        void setLayerHalfDimensions(float x, float y);

        void setLayerPositionCOM(float x, float y);
        // void setLayerPositionCorner(float x, float y); Would be complicated for updates

        void setLayerInternalShift(float x, float y);

        private:
        std::shared_ptr<EntityCollection> entity_collection;

        std::shared_ptr<OPENGL_management::Shader> shader_still;
        std::shared_ptr<OPENGL_management::Shader> shader_animated;

        glm::vec2 layer_position_COM = glm::vec2(0.0f, 0.0f);
        glm::vec2 layer_halfdimensions = glm::vec2(0.4f, 0.4f);
        glm::vec2 layer_internal_shift = glm::vec2(0.0f, 0.0f);

        std::vector<OPENGL_management::ShaderUniform> uniforms;
        bool uniforms_up_to_date = false;
        virtual void generateUniforms();

    };

}