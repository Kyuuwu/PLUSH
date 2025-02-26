#include "ShaderSpec.hpp"
#include "ShaderUniformSlotIdentifier.hpp"
#include "ShaderInputSlot.hpp"
#include "ReadFile.hpp"
#include "OpenGL_Type.hpp"
#include <iostream>
#include <fstream>

namespace PlushGraphics {
    ShaderSpec::ShaderSpec(std::string _shaderName){
        shaderNameString = _shaderName;

        std::string filePathRoot = "shaders/"+shaderNameString+"/";

        vertexShaderSourceString = PlushUtil::ReadFile::readFileIntoString(filePathRoot+"vertex.txt");
        fragmentShaderSourceString = PlushUtil::ReadFile::readFileIntoString("shaders/"+shaderNameString+"/fragment.txt");

        std::stringstream inputStream = PlushUtil::ReadFile::readFileIntoStringStream(filePathRoot+"inputs.txt");

        unsigned int inputCount;
        
        inputStream >> inputCount;

        shaderSlotLocation_t location;
        std::string typestring;
        OpenGL_Type type;
        std::string slotName;

        for(unsigned int i = 0; i < inputCount; i++){
            inputStream >> location;
            inputStream >> typestring;
            type = getTypeFromString(typestring);
            inputStream >> slotName;

            shaderInputSlotsVector.push_back(
                ShaderMetadata::ShaderInputSlot(
                    ShaderMetadata::ShaderInputSlotIdentifier(slotName, type),
                    location
                )
            );
        }

        std::stringstream uniformStream = PlushUtil::ReadFile::readFileIntoStringStream(filePathRoot+"uniforms.txt");

        unsigned int uniformCount;

        uniformStream >> uniformCount; 


        for(unsigned int i = 0; i < uniformCount; i++){
            uniformStream >> typestring;
            type = getTypeFromString(typestring);
            uniformStream >> slotName;

            shaderUniformSlotIdentifiersVector.push_back(
                ShaderMetadata::ShaderUniformSlotIdentifier(slotName, type)
            );
        }
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
        return shaderUniformSlotIdentifiersVector;
    }

    std::vector<ShaderMetadata::ShaderInputSlot> ShaderSpec::shaderInputSlots(){
        return shaderInputSlotsVector;
    }
}