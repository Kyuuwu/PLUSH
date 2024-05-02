#include "OPENGL_management_includes.h"
#include "PLUSH_core_includes.h"
#include <iostream>

namespace PLUSH
{
    Standard_Layer::Standard_Layer(std::string name, glm::vec2 layer_com, glm::vec2 layer_halfdimensions)
    {
        setName(name);
        setLayerPositionCOM(layer_com);
        setLayerHalfDimensions(layer_halfdimensions);
        collection = std::shared_ptr<InstanceCollection>(new InstanceCollection());

        defaultShader = OPENGL_management::ShaderLibrary::getShaderByName("Entity_2D_Shader");
    }

    void Standard_Layer::draw(std::vector<OPENGL_management::ShaderUniform> external_uniforms)
    {
        if(!uniforms_up_to_date){
            generateUniforms();
        }

        defaultShader->resetUniformSetChecks();
        for (std::shared_ptr<OPENGL_management::Shader> shader : alternativeShaders){
            shader->resetUniformSetChecks();
        }

        external_uniforms.insert(external_uniforms.begin(), uniforms.begin(), uniforms.end());

        for (OPENGL_management::ShaderUniform uni : external_uniforms){
            defaultShader->setUniform(uni);
            for (std::shared_ptr<OPENGL_management::Shader> shader : alternativeShaders){
                shader->setUniform(uni);
            }
        }

        std::vector<Instance_Group_Pair> instancesList = collection->getSortedInstanceGroupPairs();

        //TODO rest of render handling

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

        for(Instance_Group_Pair instpair : instancesList){
            std::shared_ptr<Instance> ent = instpair.instance;
            glm::vec3 position = ent->getPosition();
            entity_uniforms[0].value.f = position.x;
            entity_uniforms[1].value.f = position.y;

            glm::vec3 scale = ent->getScale();
            entity_uniforms[2].value.f = scale.x;
            entity_uniforms[3].value.f = scale.y;

           
            ent->drawWithShader(defaultShader.get(), entity_uniforms, false);
        }


    }
    
    void Standard_Layer::setLayerDimensions(float x, float y)
    {
        setLayerHalfDimensions(x/2.0f, y/2.0f);
    }
    
    void Standard_Layer::setLayerDimensions(glm::vec2 dimensions)
    {
        setLayerHalfDimensions(dimensions / 2.0f);
    }
    
    void Standard_Layer::setLayerHalfDimensions(float x, float y)
    {
        setLayerHalfDimensions(glm::vec2(x,y));
    }
    
    void Standard_Layer::setLayerHalfDimensions(glm::vec2 halfdimensions)
    {
        layer_halfdimensions = halfdimensions;
        uniforms_up_to_date = false;
    }
    
    void Standard_Layer::setLayerPositionCOM(float x, float y)
    {
        setLayerPositionCOM(glm::vec2(x,y));
    }
    
    void Standard_Layer::setLayerPositionCOM(glm::vec2 layer_com)
    {
        layer_position_COM = layer_com;
        uniforms_up_to_date = false;
    }
    
    void Standard_Layer::addInstance(std::weak_ptr<Instance> newInstance, int group)
    {
        newInstance.lock()->addContainingCollection(collection);
        collection->addInstance(newInstance, group);
    }
    
    void Standard_Layer::setName(std::string newName)
    {
        name = newName;
    }
    
    std::string Standard_Layer::getName()
    {
        return name;
    }
    
    std::shared_ptr<InstanceCollection> Standard_Layer::DEBUG_GET_COLLECTION()
    {
        return collection;
    }
    
    void Standard_Layer::generateUniforms()
    {
        OPENGL_management::ShaderUniform layer_halfdimensions_uniform, layer_position_uniform, layer_internal_shift_uniform;

        layer_halfdimensions_uniform.target.name = "layerHalfDimensions";
        layer_halfdimensions_uniform.target.type = OPENGL_management::OPENGL_FLOAT_VEC_2;
        layer_halfdimensions_uniform.value.fptr = &layer_halfdimensions[0];

        layer_position_uniform.target.name = "layerPosition";
        layer_position_uniform.target.type = OPENGL_management::OPENGL_FLOAT_VEC_2;
        layer_position_uniform.value.fptr = &layer_position_COM[0];

        std::vector<OPENGL_management::ShaderUniform> newUniformList;
        newUniformList.push_back(layer_halfdimensions_uniform);
        newUniformList.push_back(layer_position_uniform);
        newUniformList.push_back(layer_internal_shift_uniform);

        uniforms = newUniformList;

        uniforms_up_to_date = true;
    }
}