#include "PLUSH_core_includes.h"

#include "OPENGL_management_includes.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Helpers.h"

#include "Standard_Layer.h"

#include <iostream>

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

    glm::mat4 Instance::getModelMatrix(){
        generateModelMatrixIfNeeded();
        return modelMatrix;
    }

    void Instance::drawWithShader(OPENGL_management::Shader *shader, std::vector<OPENGL_management::ShaderUniform> external_uniforms, bool resetChecks){
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

        model->drawWithShader(shader, external_uniforms, resetChecks, texture2D_name_pairs);   
        // std::cout << "Drawing entity time: ";
        // PLUSH_helpers::outputTimeElapsed();
        // std::cout << std::endl;     
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

    std::shared_ptr<Instance> generateBasicEntity(std::string name, std::string modelname, glm::vec3 pos, glm::vec3 scale){
    std::shared_ptr<Instance> ent(new Instance(name, modelname));
        ent->getStatusPointer()->visible = true;
        ent->setScale(scale);
        ent->setPosition(pos);    

        return ent;
    }
    
    std::shared_ptr<Instance> generateBasicTexturedEntity(std::string name, std::string modelname, std::string texturename, glm::vec3 pos, glm::vec3 scale){
        std::shared_ptr<Instance> ent =  generateBasicEntity(name, modelname, pos, scale);
        ent->setTexture2DUniform("primaryTexture", texturename);

        return ent;
    }

    std::shared_ptr<Instance> generateBasicTexturedSquareEntity(std::string name, std::string texturename, glm::vec3 pos, glm::vec3 scale){
        return generateBasicTexturedEntity(name, "square2D.vx", texturename, pos, scale);
    }
    
    std::weak_ptr<Instance> Entity::getInstance(int index)
    {
        return instances[index];
    }
    
    std::weak_ptr<Instance> Entity::getInstance(std::string instanceName)
    {
        for (std::shared_ptr<Instance> inst : instances){
            if (inst->getName() == instanceName){
                return inst;
            }
        }
        throw(INSTANCE_NOT_FOUND);
    }
    
    unsigned int Entity::getNumInstances()
    {
        return instances.size();
    }
    
    std::vector<std::weak_ptr<Instance>> Entity::getInstances()
    {
        std::vector<std::weak_ptr<Instance>> weak_instances;

        for (std::shared_ptr<Instance> inst: instances){
            weak_instances.push_back(inst);
        }

        return weak_instances;
    }
    
    std::weak_ptr<Instance> Entity::addInstance(std::string name, std::string modelname)
    {
        std::shared_ptr<Instance> newInstance(new Instance(name, modelname));
        instances.push_back(newInstance);
        return newInstance;
    }
    
    void Entity::addInstanceToLayer(std::string instanceName, std::shared_ptr<Standard_Layer> layer, int group)
    {
        layer->addInstance(getInstance(instanceName), group);
    }
    
    void Entity::createInstanceInLayer(std::string instanceName, std::string modelName, std::shared_ptr<Standard_Layer> layer, int group)
    {
        layer->addInstance(addInstance(instanceName, modelName));
    }
    
}