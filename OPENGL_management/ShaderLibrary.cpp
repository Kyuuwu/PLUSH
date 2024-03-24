#include "OPENGL_management_includes.h"
#include "Exceptions.h"
#include <iostream>

namespace OPENGL_management {
    bool ShaderLibrary::isShaderLibraryInitialized(){
        return isInitialized;
    }

    void ShaderLibrary::reInitializeShaderLibrary(){
        std::vector<std::shared_ptr<Shader>> newShaderList;

        std::shared_ptr<Shader> shader(ShaderGeneration::generateShaderFromComboFile("2.combo"));

        std::shared_ptr<Shader> shadercolor(ShaderGeneration::generateShaderFromComboFile("color.combo"));

        std::shared_ptr<Shader> shadertex(ShaderGeneration::generateShaderFromComboFile("texModel.combo"));

        std::shared_ptr<Shader> tile(ShaderGeneration::generateShaderFromComboFile("Tile.combo"));
        std::shared_ptr<Shader> tilemove(ShaderGeneration::generateShaderFromComboFile("TileMoveable.combo"));

        std::shared_ptr<Shader> ent_2d(ShaderGeneration::generateShaderFromComboFile("entity_2D.combo"));
        std::shared_ptr<Shader> ent_2da(ShaderGeneration::generateShaderFromComboFile("entity_2D_animated.combo"));

        newShaderList.push_back(tile);
        newShaderList.push_back(tilemove);
        newShaderList.push_back(shader);
        newShaderList.push_back(shadercolor);
        newShaderList.push_back(shadertex);
        newShaderList.push_back(ent_2d);
        newShaderList.push_back(ent_2da);

        shaderList = newShaderList;
        isInitialized = true;
    }

    void ShaderLibrary::initializeShaderLibraryIfNeeded(){
        if (!isInitialized){
            reInitializeShaderLibrary();
        }
    }

    std::shared_ptr<Shader> ShaderLibrary::getShaderByName(std::string name){
        initializeShaderLibraryIfNeeded();

        for (std::shared_ptr<Shader> shader : shaderList){
            if(shader->getName() == name){
                return shader;
            }
        }

        throw(SHADER_NOT_FOUND);
    }
}