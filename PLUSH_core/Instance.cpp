#include "OPENGL_management_includes.h"
#include "PLUSH_core_includes.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace PLUSH {
    Instance::Instance(std::string name, std::shared_ptr<OPENGL_management::Model> model, InstanceStatus status):
        model(model),
        rotation(new RotationHandler())
    {
        this->name = name;
        this->status = status;
    }

    Instance::Instance(std::string name, std::string modelname, InstanceStatus status):
    Instance(name, OPENGL_management::ModelLibrary::getModelByName(modelname), status){}

    std::string Instance::getName(){
        return name;
    }

    void Instance::generateModelMatrixIfNeeded(){
        if (positionUpdated || scaleUpdated || rotation->wasUpdated()){
            generateModelMatrix();
        }
    }

    void Instance::generateModelMatrix(){
        positionUpdated = false;
        scaleUpdated = false;
        rotation->resetUpdateCheck();

        modelMatrix =  glm::translate(rotation->getRotationMatrix()*glm::scale( glm::mat4( 1.0f ) ,scale), position);
    }
    
    bool Instance::tryToFulfillUniform(std::shared_ptr<OPENGL_management::Shader> shader, OPENGL_management::ShaderUniformTarget target)
    {
        bool isfulfilled = false;

        StandardUniformCode code = getStandardUniformCode(target);

        switch (code) {
            case ENTITY_POSITION_2D_X:{
                OPENGL_management::ShaderUniform uniform;
                uniform.target = target;
                uniform.value.f = position.x;
                shader->setUniform(uniform);
                isfulfilled = true;
                break;
            }

            case ENTITY_POSITION_2D_Y:{
                OPENGL_management::ShaderUniform uniform;
                uniform.target = target;
                uniform.value.f = position.y;
                shader->setUniform(uniform);
                isfulfilled = true;
                break;
            }

            case ENTITY_SCALE_2D_X:{
                OPENGL_management::ShaderUniform uniform;
                uniform.target = target;
                uniform.value.f = scale.x;
                shader->setUniform(uniform);
                isfulfilled = true;
                break;
            }

            case ENTITY_SCALE_2D_Y:{
                OPENGL_management::ShaderUniform uniform;
                uniform.target = target;
                uniform.value.f = scale.y;
                shader->setUniform(uniform);
                isfulfilled = true;
                break;
            }

            case ENTITY_PRIMARY_TEXTURE:{
                bool foundMatchingInstanceTexture = false;
                for(OPENGL_management::TextureNamePair pair : texture2D_name_pairs){
                    if (pair.uniformname == target.name){
                        shader->setTexture2DUniform(pair, OPENGL_management::TextureLibrary::getNextEntityReservedTextureUnit());
                        foundMatchingInstanceTexture = true;
                        break;
                    }
                }

                if (!foundMatchingInstanceTexture){
                    model->useDefaultTexture2D(shader.get(), target.name);
                }
                isfulfilled = true;
                break;
            }

            default:
                break;
        }

        // if(isfulfilled){
        //     return true;
        // }

        // for(OPENGL_management::ShaderUniform uniform : uniforms){
        //     if(uniform.target.name == target.name && uniform.target.type == target.type){
        //         shader->setUniform(uniform);
        //         return true;
        //     }
        // }

        //TODO: try with plugins

        return isfulfilled;
    }

    glm::mat4 Instance::getModelMatrix(){
        generateModelMatrixIfNeeded();
        return modelMatrix;
    }

    void Instance::drawWithShader(OPENGL_management::Shader *shader, std::vector<OPENGL_management::ShaderUniform> external_uniforms, bool resetPerInstanceChecks){
        if(!status.visible){
            return;
        }

        generateModelMatrixIfNeeded();

        OPENGL_management::ShaderUniform modelmatrixuniform;
        modelmatrixuniform.target.name = "modelMatrix";
        modelmatrixuniform.target.type = OPENGL_management::OPENGL_FLOAT_MAT_4;

        modelmatrixuniform.value.fptr = &modelMatrix[0][0];

        external_uniforms.push_back(modelmatrixuniform);
        external_uniforms.insert(external_uniforms.begin(), internal_uniforms.begin(), internal_uniforms.end());

        // external_uniforms.insert(external_uniforms.begin(), texture_uniforms.begin(), texture_uniforms.end());

        //add animation uniforms
        if (status.animated){
            OPENGL_management::ShaderUniform animation_index;
            animation_index.target.name = "textureGridIndex";
            animation_index.target.type = OPENGL_management::OPENGL_UINT;
            animation_index.value.u = status.animation_index;
            
            external_uniforms.push_back(animation_index);
        }

        // std::cout << "Constructing uniform list time: ";
        // PLUSH_helpers::outputTimeElapsed();
        // std::cout << std::endl;
        

        model->drawWithShader(shader, external_uniforms, resetPerInstanceChecks, texture2D_name_pairs);   
        // std::cout << "Drawing entity time: ";
        // PLUSH_helpers::outputTimeElapsed();
        // std::cout << std::endl;     
    }
    
    void Instance::newDrawWithShader(std::shared_ptr<OPENGL_management::Shader> shader)
    {
        model->newDrawWithShader(shader);
    }

    std::shared_ptr<RotationHandler> Instance::getRotationHandler(){
        return rotation;
    }

    void Instance::setInternalUniforms(std::vector<OPENGL_management::ShaderUniform> uniforms){
        internal_uniforms = uniforms;
    }

    void Instance::addInternalUniform(OPENGL_management::ShaderUniform uniform){
        internal_uniforms.push_back(uniform);
    }

    std::vector<OPENGL_management::ShaderUniform> Instance::getInternalUniforms(){
        return internal_uniforms;
    }

    void Instance::setTexture2DUniform(std::string uniformname, std::string texturename){
        OPENGL_management::TextureNamePair tex;
        tex.uniformname = uniformname;
        tex.texturename = texturename;

        for(int i = texture2D_name_pairs.size() - 1; i >=0 ; i--){
            if(texture2D_name_pairs.at(i).uniformname == uniformname){
                texture2D_name_pairs.erase(texture2D_name_pairs.begin() + i);
            }
        }

        texture2D_name_pairs.push_back(tex);
    }

    std::shared_ptr<Instance> Instance::copy(){
        std::shared_ptr<Instance> copied(new Instance(name, model, status));
        copied->setPosition(position);

        std::shared_ptr<RotationHandler> rotationcopy = rotation->copy();

        copied->setRotationHandler(rotationcopy);

        return copied;
    }

    void Instance::setRotationHandler(std::shared_ptr<RotationHandler> rotationHandler){

        rotation = rotationHandler;
    }

    void Instance::setPosition(glm::vec3 newPosition){
        position = newPosition;
        positionUpdated = true;
    }
    
    int32_t Instance::getLayerOrder() const
    {
        return layerOrder;
    }
    
    void Instance::setLayerOrder(int32_t new_layerorder)
    {
        layerOrder = new_layerorder;
    }
    
    bool Instance::compareLayerOrder(const Instance& a, const Instance& b) 
    {
        return a.getLayerOrder() < b.getLayerOrder();
    }
    
    bool Instance::compareLayerOrderShared(const std::shared_ptr<Instance>& a, const std::shared_ptr<Instance>& b) 
    {
        return a->getLayerOrder() < b->getLayerOrder();
    }
    
    bool Instance::compareLayerOrderWeak(const std::weak_ptr<Instance>& a, const std::weak_ptr<Instance>& b) 
    {
        return a.lock()->getLayerOrder() < b.lock()->getLayerOrder();
    }

    glm::vec3 Instance::getPosition(){
        return position;
    }

    void Instance::setScale(glm::vec3 newScale){
        scale = newScale;
        scaleUpdated = true;
    }

    glm::vec3 Instance::getScale(){
        return scale;
    }

    InstanceStatus Instance::getStatus(){
        return status;
    }

    InstanceStatus* Instance::getStatusPointer(){
        return &status;
    }

    void Instance::setStatus(InstanceStatus newstatus){
        status = newstatus;
    }
    
    void Instance::setParentEntity(std::shared_ptr<Entity> parent)
    {
        parentEntity = parent;
    }
    
    std::shared_ptr<Entity> Instance::getParentEntity()
    {
        return parentEntity.lock();
    }
    
    void Instance::addContainingCollection(std::weak_ptr<InstanceCollection> collection)
    {
        containingCollections.push_back(collection);
    }
    
    OPENGL_management::Pair_Unfulfilled_Overriden_UniformTarget Instance::fulfillShaderRequirements(
        std::shared_ptr<OPENGL_management::Shader> shader,
        std::vector<OPENGL_management::ShaderUniformTarget> unfulfilledTargets,
        std::vector<OPENGL_management::ShaderUniformTarget> fulfilledTargets)
    {
        OPENGL_management::Pair_Unfulfilled_Overriden_UniformTarget returnList;

        for(size_t i = 0; i < fulfilledTargets.size();){
            OPENGL_management::ShaderUniformTarget target = fulfilledTargets[i];
            bool successfullyFilled = tryToFulfillUniform(shader, target);
            if(successfullyFilled){
                returnList.overridenTargets.push_back(target);
            }else{
                i++;
            }
        }

        for(size_t i = 0; i < unfulfilledTargets.size();){
            OPENGL_management::ShaderUniformTarget target = unfulfilledTargets[i];
            bool successfullyFilled = tryToFulfillUniform(shader, target);
            if(successfullyFilled){
                fulfilledTargets.push_back(target); //unnecessary but keeping for now
                unfulfilledTargets.erase(unfulfilledTargets.begin() + i);
            }else{
                i++;
            }
        }

        returnList.unfulfilledTargets = unfulfilledTargets;

        return returnList;
    }
}