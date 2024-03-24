#include "PLUSH_core_includes.h"

#include "OPENGL_management_includes.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Helpers.h"

#include <iostream>

namespace PLUSH {
    Entity::Entity(std::string name, std::shared_ptr<OPENGL_management::Model> model, EntityStatus status):
        model(model),
        rotation(new RotationHandler())
    {
        this->name = name;
        this->status = status;
    }

    Entity::Entity(std::string name, std::string modelname, EntityStatus status):
    Entity(name, OPENGL_management::ModelLibrary::getModelByName(modelname), status){}

    std::string Entity::getName(){
        return name;
    }

    void Entity::generateModelMatrixIfNeeded(){
        if (positionUpdated || scaleUpdated || rotation->wasUpdated()){
            generateModelMatrix();
        }
    }

    void Entity::generateModelMatrix(){
        positionUpdated = false;
        scaleUpdated = false;
        rotation->resetUpdateCheck();

        modelMatrix =  glm::translate(rotation->getRotationMatrix()*glm::scale(scale), position);
    }

    glm::mat4 Entity::getModelMatrix(){
        generateModelMatrixIfNeeded();
        return modelMatrix;
    }

    void Entity::drawWithShader(OPENGL_management::Shader *shader, std::vector<OPENGL_management::ShaderUniform> external_uniforms, bool resetChecks){
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

    std::shared_ptr<RotationHandler> Entity::getRotationHandler(){
        return rotation;
    }

    void Entity::setInternalUniforms(std::vector<OPENGL_management::ShaderUniform> uniforms){
        internal_uniforms = uniforms;
    }

    void Entity::addInternalUniform(OPENGL_management::ShaderUniform uniform){
        internal_uniforms.push_back(uniform);
    }

    std::vector<OPENGL_management::ShaderUniform> Entity::getInternalUniforms(){
        return internal_uniforms;
    }

    void Entity::setTexture2DUniform(std::string uniformname, std::string texturename){
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

    std::shared_ptr<Entity> Entity::copy(){
        std::shared_ptr<Entity> copied(new Entity(name, model, status));
        copied->setPosition(position);

        std::shared_ptr<RotationHandler> rotationcopy = rotation->copy();

        copied->setRotationHandler(rotationcopy);

        return copied;
    }

    void Entity::setRotationHandler(std::shared_ptr<RotationHandler> rotationHandler){

        rotation = rotationHandler;
    }

    void Entity::setPosition(glm::vec3 newPosition){
        position = newPosition;
        positionUpdated = true;
    }

    glm::vec3 Entity::getPosition(){
        return position;
    }

    void Entity::setScale(glm::vec3 newScale){
        scale = newScale;
        scaleUpdated = true;
    }

    glm::vec3 Entity::getScale(){
        return scale;
    }

    EntityStatus Entity::getStatus(){
        return status;
    }

    EntityStatus* Entity::getStatusPointer(){
        return &status;
    }

    void Entity::setStatus(EntityStatus newstatus){
        status = newstatus;
    }
}