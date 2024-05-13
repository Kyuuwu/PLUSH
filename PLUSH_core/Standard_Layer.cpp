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
    
    OPENGL_management::Pair_Unfulfilled_Fulfilled_UniformTarget Standard_Layer::fulfillShaderRequirements(
        std::shared_ptr<OPENGL_management::Shader> shader,
        std::shared_ptr<Instance> instance, 
        std::vector<OPENGL_management::ShaderUniformTarget> unfulfilledTargets,
        std::vector<OPENGL_management::ShaderUniformTarget> fulfilledTargets)
    {
        
        for(size_t i = 0; i < unfulfilledTargets.size();){
            OPENGL_management::ShaderUniformTarget target = unfulfilledTargets[i];
            bool successfullyFilled = tryToFulfillUniform(shader, target);
            if(successfullyFilled){
                fulfilledTargets.push_back(target);
                unfulfilledTargets.erase(unfulfilledTargets.begin() + i);
            }else{
                i++;
            }
        }

        OPENGL_management::Pair_Unfulfilled_Overriden_UniformTarget returned_list = 
            instance->fulfillShaderRequirements(
                shader,
                unfulfilledTargets, 
                fulfilledTargets);
        
        // std::vector<OPENGL_management::ShaderUniformTarget> unfulfilledTargetsAfterInstance = returned_list.unfulfilledTargets;
        
        //TODO handle unfulfilled

        OPENGL_management::Pair_Unfulfilled_Fulfilled_UniformTarget returnvalues;

        unfulfilledTargets.insert(
            unfulfilledTargets.begin(), 
            returned_list.overridenTargets.begin(), 
            returned_list.overridenTargets.end());

        for(OPENGL_management::ShaderUniformTarget overridenTarget : returned_list.overridenTargets){
            for(size_t i = 0; i < fulfilledTargets.size();){
                if(overridenTarget.name == fulfilledTargets[i].name && overridenTarget.type == fulfilledTargets[i].type){
                    fulfilledTargets.erase(fulfilledTargets.begin() + i);
                }else{
                    i++;
                }
            }
        }

        returnvalues.unfulfilledTargets = unfulfilledTargets;
        returnvalues.fulfilledTargets = fulfilledTargets;

        
        return returnvalues;
    }
    
    bool Standard_Layer::tryToFulfillUniform(std::shared_ptr<OPENGL_management::Shader> shader, OPENGL_management::ShaderUniformTarget target)
    {
        bool isfulfilled = false;

        StandardUniformCode code = getStandardUniformCode(target);

        switch (code){
            case WINDOW_ASPECT_RATIO:{
                OPENGL_management::ShaderUniform uniform;
                uniform.target = target;
                uniform.value.f = windowBeingDrawnIn->getAspectRatio();
                shader->setUniform(uniform);
                isfulfilled = true;
                break;
            }

            case LAYER_POSITION:{
                OPENGL_management::ShaderUniform uniform;
                uniform.target = target;
                uniform.value.fptr = &layer_position_COM;
                shader->setUniform(uniform);
                isfulfilled = true;
                break;
            }

            case LAYER_HALF_DIMENSIONS:{
                OPENGL_management::ShaderUniform uniform;
                uniform.target = target;
                uniform.value.fptr = &layer_halfdimensions;
                shader->setUniform(uniform);
                isfulfilled = true;
                break;
            }

            case LAYER_OFFSET:{
                OPENGL_management::ShaderUniform uniform;
                uniform.target = target;
                uniform.value.fptr = &layer_offset;
                shader->setUniform(uniform);
                isfulfilled = true;
                break;
            }

            default:
                break;
        }

        // for(OPENGL_management::ShaderUniform uniform : uniforms){
        //     if(uniform.target.name == target.name && uniform.target.type == target.type){
        //         shader->setUniform(uniform);
        //         return true;
        //     }
        // }

        //TODO: try with plugins

        return isfulfilled;
    }
    
    void Standard_Layer::draw(
        WindowHandler* window,
        std::vector<OPENGL_management::ShaderUniform> external_uniforms)
    {
        windowBeingDrawnIn = window;

        if(!uniforms_up_to_date){
            generateUniforms();
        }

        OPENGL_management::Pair_Unfulfilled_Fulfilled_UniformTarget default_target_list; 
        default_target_list.unfulfilledTargets = defaultShader->getUniformTargets();

        std::vector<OPENGL_management::Pair_Unfulfilled_Fulfilled_UniformTarget> target_lists;

        for(std::shared_ptr<OPENGL_management::Shader> altshader : alternativeShaders){
            OPENGL_management::Pair_Unfulfilled_Fulfilled_UniformTarget new_target_list;
            new_target_list.unfulfilledTargets=altshader->getUniformTargets();
            target_lists.push_back(new_target_list);
        }

        std::vector<Instance_Group_Pair> instancesList = collection->getSortedInstanceGroupPairs();

        for(Instance_Group_Pair pair: instancesList){
            std::shared_ptr<OPENGL_management::Shader> shaderToUse;
            
            if(pair.group == 0){
                OPENGL_management::Pair_Unfulfilled_Fulfilled_UniformTarget newPair = 
                    fulfillShaderRequirements(
                        defaultShader, 
                        pair.instance, 
                        default_target_list.unfulfilledTargets, 
                        default_target_list.fulfilledTargets);
                default_target_list = newPair;
                shaderToUse = defaultShader;
            }else{
                size_t altshader_num = pair.group - 1;
                if(altshader_num < alternativeShaders.size()){
                    OPENGL_management::Pair_Unfulfilled_Fulfilled_UniformTarget newPair = 
                        fulfillShaderRequirements(
                            alternativeShaders[altshader_num], 
                            pair.instance, 
                            target_lists[altshader_num].unfulfilledTargets, 
                            target_lists[altshader_num].fulfilledTargets);
                    target_lists.erase(target_lists.begin()+altshader_num);
                    target_lists.insert(target_lists.begin()+altshader_num, newPair);
                }
                else{
                    OPENGL_management::Pair_Unfulfilled_Fulfilled_UniformTarget newPair = 
                        fulfillShaderRequirements(
                            defaultShader, 
                            pair.instance, 
                            default_target_list.unfulfilledTargets, 
                            default_target_list.fulfilledTargets);
                    default_target_list = newPair;
                    shaderToUse = defaultShader;
                }
            }
            pair.instance->newDrawWithShader(shaderToUse);
        }

        // defaultShader->resetPerLayerUniformSetChecks();
        // for (std::shared_ptr<OPENGL_management::Shader> shader : alternativeShaders){
        //     shader->resetPerLayerUniformSetChecks();
        // }

        // external_uniforms.insert(external_uniforms.begin(), uniforms.begin(), uniforms.end());

        // for (OPENGL_management::ShaderUniform uni : external_uniforms){
        //     defaultShader->setUniform(uni);
        //     for (std::shared_ptr<OPENGL_management::Shader> shader : alternativeShaders){
        //         shader->setUniform(uni);
        //     }
        // }

        //TODO rest of render handling

        // std::vector<OPENGL_management::ShaderUniform> entity_uniforms;
        // OPENGL_management::ShaderUniform EntityX, EntityY, EntityScaleX, EntityScaleY;

        // EntityX.target.name = "EntityX";
        // EntityX.target.type = OPENGL_management::OPENGL_FLOAT;
        // EntityY.target.name = "EntityY";
        // EntityY.target.type = OPENGL_management::OPENGL_FLOAT;

        // EntityScaleX.target.name = "EntityScaleX";
        // EntityScaleX.target.type = OPENGL_management::OPENGL_FLOAT;
        // EntityScaleY.target.name = "EntityScaleY";
        // EntityScaleY.target.type = OPENGL_management::OPENGL_FLOAT;

        // entity_uniforms.push_back(EntityX);
        // entity_uniforms.push_back(EntityY);
        // entity_uniforms.push_back(EntityScaleX);
        // entity_uniforms.push_back(EntityScaleY);

        // for(Instance_Group_Pair instpair : instancesList){
        //     std::shared_ptr<Instance> ent = instpair.instance;
        //     glm::vec3 position = ent->getPosition();
        //     entity_uniforms[0].value.f = position.x;
        //     entity_uniforms[1].value.f = position.y;

        //     glm::vec3 scale = ent->getScale();
        //     entity_uniforms[2].value.f = scale.x;
        //     entity_uniforms[3].value.f = scale.y;

           
        //     ent->drawWithShader(defaultShader.get(), entity_uniforms, true);
        // }
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
    
    void Standard_Layer::setLayerOffset(float x, float y)
    {
        setLayerOffset(glm::vec2(x,y));
    }
    
    void Standard_Layer::setLayerOffset(glm::vec2 new_layeroffset)
    {
        layer_offset = new_layeroffset;
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

        layer_internal_shift_uniform.target.name = "layerOffset";
        layer_internal_shift_uniform.target.type = OPENGL_management::OPENGL_FLOAT_VEC_2;
        layer_internal_shift_uniform.value.fptr = &layer_offset[0];

        std::vector<OPENGL_management::ShaderUniform> newUniformList;
        newUniformList.push_back(layer_halfdimensions_uniform);
        newUniformList.push_back(layer_position_uniform);
        newUniformList.push_back(layer_internal_shift_uniform);

        uniforms = newUniformList;

        uniforms_up_to_date = true;
    }
}