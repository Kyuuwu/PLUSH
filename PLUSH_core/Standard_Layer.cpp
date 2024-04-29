#include "OPENGL_management_includes.h"
#include "PLUSH_core_includes.h"

namespace PLUSH
{
    Standard_Layer::Standard_Layer(std::string name, glm::vec2 layer_com, glm::vec2 layer_halfdimensions)
    {
        setName(name);
        setLayerPositionCOM(layer_com);
        setLayerHalfDimensions(layer_halfdimensions);
        collection = std::shared_ptr<InstanceCollection>(new InstanceCollection());
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