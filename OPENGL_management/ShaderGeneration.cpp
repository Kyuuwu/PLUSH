#include "OPENGL_management_includes.h"

#include "Helpers.h"
#include "Exceptions.h"

#include <sstream>
#include <iostream>

namespace OPENGL_management {
    Shader* ShaderGeneration::generateShaderFromFiles(const char *vertexPath, const char *fragmentPath, const char * name){
        return new Shader(getVertexShaderPath(vertexPath).c_str(), getFragmentShaderPath(fragmentPath).c_str(), name);
    }

    Shader* ShaderGeneration::generateShaderFromComboFile(const char *comboPath){
        std::stringstream combostream = PLUSH_helpers::getStreamFromFile(getComboShaderPath(comboPath));

        std::string name, vertexPath, fragmentPath;

        combostream >> name;
        combostream >> vertexPath;
        combostream >> fragmentPath;

        if(!combostream){
            throw(PLUSH_helpers::FILE_INCOMPLETE);
        }

        return generateShaderFromFiles(vertexPath.c_str(), fragmentPath.c_str(), name.c_str());
    }
    
    Shader* ShaderGeneration::generateShaderFromComboFile(std::string comboPath)
    {
        generateShaderFromComboFile(comboPath.c_str());
    }
    
    std::shared_ptr<Shader> ShaderGeneration::generateShaderSharedPtrFromFiles(const char* vertexPath, const char* fragmentPath, const char *name)
    {
        return std::shared_ptr<Shader>(new Shader(getVertexShaderPath(vertexPath).c_str(), getFragmentShaderPath(fragmentPath).c_str(), name));
    }
    
    std::shared_ptr<Shader> ShaderGeneration::generateShaderSharedPtrFromComboFile(std::string comboPath)
    {
        std::stringstream combostream = PLUSH_helpers::getStreamFromFile(getComboShaderPath(comboPath));

        std::string name, vertexPath, fragmentPath;

        combostream >> name;
        combostream >> vertexPath;
        combostream >> fragmentPath;

        if(!combostream){
            throw(PLUSH_helpers::FILE_INCOMPLETE);
        }

        return generateShaderSharedPtrFromFiles(vertexPath.c_str(), fragmentPath.c_str(), name.c_str());
    }
}