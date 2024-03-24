#include "OPENGL_includes.h"
#include "OPENGL_management_includes.h"

#include <iostream>
#include "Helpers.h"

namespace OPENGL_management {
    Model::Model(std::string name, unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int num_vx, std::vector<ShaderInput> inputs){
        this->name = name;
        this->VAO = vao;
        this->VBO = vbo;
        this->EBO = ebo;
        this->number_of_vertices = num_vx;
        usingEBO = true;
        vertex_inputs = inputs;
    }

    Model::Model(std::string name, unsigned int vao, unsigned int vbo, unsigned int num_vx, std::vector<ShaderInput> inputs){
        this->name = name;
        this->VAO = vao;
        this->VBO = vbo;
        this->number_of_vertices = num_vx;
        vertex_inputs = inputs;
    }

    void Model::drawWithShader(Shader *shader, std::vector<ShaderUniform> external_uniforms, bool resetSetChecks , std::vector<TextureNamePair> external_textures){
        // Maybe check compatibility here

        shader->use();


        // std::cout << "Use shader time: ";
        // PLUSH_helpers::outputTimeElapsed();
        // std::cout << std::endl;

        if(resetSetChecks){
            shader->resetUniformSetChecks();
        }

        // std::cout << "Reset uniform checks for model " << name << std::endl;

        for (ShaderUniform uniform : external_uniforms){
            shader->setUniform(uniform.value, uniform.target);
        }

        for (ShaderUniform uniform : internal_uniforms){
            shader->setUniform(uniform.value, uniform.target);
        }

        for(unsigned int i = 0 ; i < texture2D_name_pairs.size() + external_textures.size(); i++){
            if(i < texture2D_name_pairs.size()){
                useTexture2D(shader, texture2D_name_pairs.at(i), i);
            } else{
                useTexture2D(shader, external_textures.at(i - texture2D_name_pairs.size()), i);
            }
        }

        // std::cout << "Setting uniforms time: ";
        // PLUSH_helpers::outputTimeElapsed();
        // std::cout << std::endl;

        // std::cout << "Setting unset uniforms to default for model " << name << std::endl;

        // if (resetSetChecks){
        //     shader->setUnsetUniformsToDefault();
        // } // This check was a mistake??

        shader->setUnsetUniformsToDefault();


        // std::cout << "Unset uniforms set to default for model " << name << std::endl << std::endl;

        // std::cout << "Defaulting uniforms time: ";
        // PLUSH_helpers::outputTimeElapsed();
        // std::cout << std::endl;
        draw();


        // std::cout << "Drawing model time: ";
        // PLUSH_helpers::outputTimeElapsed();
        // std::cout << std::endl;
    }

    void Model::draw(){
        glBindVertexArray(VAO);
        if (usingEBO){
            glDrawElements(GL_TRIANGLES, number_of_vertices, GL_UNSIGNED_INT, 0);
        }else {
            glDrawArrays(GL_TRIANGLES, 0, number_of_vertices);
        }
        glBindVertexArray(0);
    }

    bool Model::checkInputCompatibility(Shader *shader){
        std::vector<ShaderInput> shader_inputs = shader->getInputs();

        for (ShaderInput s_in : shader_inputs){
            bool matchFound = false;
            for (ShaderInput v_in : vertex_inputs){
                if (s_in.location == v_in.location && s_in.name == v_in.name && s_in.type == v_in.type){
                    matchFound = true;
                    break;
                }
            }
            if (!matchFound){
                return false;
            }
        }

        return true;
    }

    void Model::setInternalUniforms(std::vector<ShaderUniform> uniforms){
        internal_uniforms = uniforms;
    }

    std::vector<ShaderUniform> Model::getInternalUniforms(){
        return internal_uniforms;
    }

    void Model::addInternalUniform(ShaderUniform uniform){
        internal_uniforms.push_back(uniform);
    }

    void Model::setTextures2D(std::vector<std::shared_ptr<Texture2D>> textures){
        textures_2D = textures;
    }

    std::string Model::getName(){
        return name;
    }

    void Model::setTexture2DUniform(std::string uniformname, std::string texturename){
        ShaderUniform texUniform;
        texUniform.target.name = uniformname;
        texUniform.target.type = OPENGL_SAMPLER2D;
        
        for(int i = texture_uniforms.size()-1 ; i >= 0 ; i++){
            if(texture_uniforms.at(i).target.name == uniformname){
                texture_uniforms.erase(texture_uniforms.begin() + i);
            }
        }

        for(int i = 0 ; i < textures_2D.size() ; i++){
            if(textures_2D.at(i)->getName()==texturename){
                texUniform.value.i = i;
                break;
            }
        }

        texture_uniforms.push_back(texUniform);
    }

    std::vector<TextureNamePair> Model::getTextures2D(){
        return texture2D_name_pairs;
    }

    void Model::useTexture2D(Shader* shader, TextureNamePair texture, unsigned int texture_unit){
        Texture2D* textureptr = TextureLibrary::getTexture2DByName(texture.texturename).get();
        
        textureptr->use(texture_unit);

        if (textureptr->getIsGrid()){
            ShaderUniform texgridwidth, texgridheight;
            texgridwidth.target.name = "textureGridWidth";
            texgridheight.target.name = "textureGridHeight";

            texgridwidth.target.type = OPENGL_UINT;
            texgridheight.target.type = OPENGL_UINT;

            texgridwidth.value.u = textureptr->getGridWidth();
            texgridheight.value.u = textureptr->getGridHeight();

            shader->setUniform(texgridwidth.value, texgridwidth.target);
            shader->setUniform(texgridheight.value, texgridheight.target);
        }

        ShaderUniform texture_uniform;
        texture_uniform.target.name = texture.uniformname;
        texture_uniform.target.type = OPENGL_SAMPLER2D;
        texture_uniform.value.i = (int)texture_unit;

        shader->setUniform(texture_uniform.value, texture_uniform.target);
    }

    void Model::setTextures2D(std::vector<TextureNamePair> textures){
        texture2D_name_pairs = textures;
    }

    void Model::addTexture2D(TextureNamePair texture){
        texture2D_name_pairs.push_back(texture);
    }

    void Model::addTexture2D(std::string uniformname, std::string texturename){
        TextureNamePair tex;
        tex.texturename = texturename;
        tex.uniformname = uniformname;
        addTexture2D(tex);
    }
}