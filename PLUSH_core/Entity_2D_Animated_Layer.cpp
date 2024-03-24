#include "Entity_2D_Animated_Layer.h"
#include "Entity_Collections.h"
#include "Entity.h"
#include "OPENGL_management_includes.h"

#include <iostream>

namespace PLUSH{
    Entity_2D_Animated_Layer::Entity_2D_Animated_Layer(std::string name):
    DrawableLayer(name)
    {
        shader_still = OPENGL_management::ShaderLibrary::getShaderByName("Entity_2D_Shader");
        shader_animated = OPENGL_management::ShaderLibrary::getShaderByName("Entity_2D_Animated_Shader");

        // std::vector<OPENGL_management::ShaderUniformSlot> slots = shader_animated->getUniformSlots();

        // for(OPENGL_management::ShaderUniformSlot slot : slots){
        //     std::cout << slot.name << std::endl;
        //     std::cout << slot.type << std::endl<<std::endl;
        // }

    }

    void Entity_2D_Animated_Layer::setEntityCollection(std::shared_ptr<EntityCollection> collection){
        entity_collection = collection;
    }

    void Entity_2D_Animated_Layer::setLayerDimensions(float x, float y){
        setLayerHalfDimensions(x/2.0, y/2.0);
    }

    void Entity_2D_Animated_Layer::setLayerHalfDimensions(float x, float y){
        layer_halfdimensions = glm::vec2(x,y);
        uniforms_up_to_date = false;
    }

    void Entity_2D_Animated_Layer::setLayerPositionCOM(float x, float y){
        layer_position_COM = glm::vec2(x,y);
        uniforms_up_to_date = false;
    }

    void Entity_2D_Animated_Layer::setLayerInternalShift(float x, float y){
        layer_internal_shift = glm::vec2(x,y);
        uniforms_up_to_date = false;
    }

    void Entity_2D_Animated_Layer::generateUniforms(){
        OPENGL_management::ShaderUniform layer_halfdimensions_uniform, layer_position_uniform, layer_internal_shift_uniform;

        layer_halfdimensions_uniform.target.name = "layerHalfDimensions";
        layer_halfdimensions_uniform.target.type = OPENGL_management::OPENGL_FLOAT_VEC_2;
        layer_halfdimensions_uniform.value.fptr = &layer_halfdimensions[0];

        layer_position_uniform.target.name = "layerPosition";
        layer_position_uniform.target.type = OPENGL_management::OPENGL_FLOAT_VEC_2;
        layer_position_uniform.value.fptr = &layer_position_COM[0];

        layer_internal_shift_uniform.target.name = "layerOffset";
        layer_internal_shift_uniform.target.type = OPENGL_management::OPENGL_FLOAT_VEC_2;
        layer_internal_shift_uniform.value.fptr = &layer_internal_shift[0];

        std::vector<OPENGL_management::ShaderUniform> newUniformList;
        newUniformList.push_back(layer_halfdimensions_uniform);
        newUniformList.push_back(layer_position_uniform);
        newUniformList.push_back(layer_internal_shift_uniform);

        uniforms = newUniformList;

        uniforms_up_to_date = true;
    }

    void Entity_2D_Animated_Layer::draw(std::vector<OPENGL_management::ShaderUniform> external_uniforms){
        if(!uniforms_up_to_date){
            generateUniforms();
        }

        shader_still->resetUniformSetChecks();
        shader_animated->resetUniformSetChecks();

        external_uniforms.insert(external_uniforms.begin(), uniforms.begin(), uniforms.end());

        for (OPENGL_management::ShaderUniform uni : external_uniforms){
            shader_still->setUniform(uni.value, uni.target);
            shader_animated->setUniform(uni.value, uni.target);
        }

        std::vector<std::shared_ptr<Entity>> entities = entity_collection->getEntitiesToRender();

        std::vector<OPENGL_management::ShaderUniform> entity_uniforms;

        OPENGL_management::ShaderUniform EntityX, EntityY, EntityScaleX, EntityScaleY;

        EntityX.target.name = "EntityX";
        EntityX.target.type = OPENGL_management::OPENGL_FLOAT;
        EntityY.target.name = "EntityY";
        EntityY.target.type = OPENGL_management::OPENGL_FLOAT;

        EntityScaleX.target.name = "EntityScaleX";
        EntityScaleX.target.type = OPENGL_management::OPENGL_FLOAT;
        EntityScaleY.target.name = "EntityScaleY";
        EntityScaleY.target.type = OPENGL_management::OPENGL_FLOAT;

        entity_uniforms.push_back(EntityX);
        entity_uniforms.push_back(EntityY);
        entity_uniforms.push_back(EntityScaleX);
        entity_uniforms.push_back(EntityScaleY);

        for(std::shared_ptr<Entity> ent : entities){
            glm::vec3 position = ent->getPosition();
            entity_uniforms[0].value.f = position.x;
            entity_uniforms[1].value.f = position.y;

            glm::vec3 scale = ent->getScale();
            entity_uniforms[2].value.f = scale.x;
            entity_uniforms[3].value.f = scale.y;

            if (ent->getStatusPointer()->animated) {
                ent->drawWithShader(shader_animated.get(), entity_uniforms, false);
                
                unsigned int anim_index = ent->getStatusPointer()->animation_index;
                if(anim_index == ent->getStatusPointer()->animation_loop_end){
                    ent->getStatusPointer()->animation_index = ent->getStatusPointer()->animation_loop_start;
                }
                else{
                    ent->getStatusPointer()->animation_index += 1;
                }
            }else{
                ent->drawWithShader(shader_still.get(), entity_uniforms, false);
            }
        }

    }
}