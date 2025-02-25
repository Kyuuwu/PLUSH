#include "ShaderSpec.hpp"
#include "ShaderUniformSlotIdentifier.hpp"
#include "ShaderInputSlot.hpp"
#include "ReadFile.hpp"
#include <iostream>
#include <fstream>

namespace PlushGraphics {
    ShaderSpec::ShaderSpec(std::string _shaderName){
        shaderNameString = _shaderName;

        std::string filePathRoot = "shaders/"+shaderNameString+"/";

        vertexShaderSourceString = PlushUtil::ReadFile::readFileIntoString(filePathRoot+"vertex.txt");
        fragmentShaderSourceString = PlushUtil::ReadFile::readFileIntoString("shaders/"+shaderNameString+"/fragment.txt");
    }

    std::string ShaderSpec::shaderName(){
        return shaderNameString;
    }

    std::string ShaderSpec::vertexShaderSource(){
        return vertexShaderSourceString;
    }

    std::string ShaderSpec::fragmentShaderSource(){
        return fragmentShaderSourceString;
    }

    std::vector<ShaderMetadata::ShaderUniformSlotIdentifier> ShaderSpec::shaderUniformSlotIdentifiers(){
        return std::vector<ShaderMetadata::ShaderUniformSlotIdentifier>();
    }

    std::vector<ShaderMetadata::ShaderInputSlot> ShaderSpec::shaderInputSlots(){
        return std::vector<ShaderMetadata::ShaderInputSlot>();
    }
}