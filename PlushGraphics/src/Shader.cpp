#include "Shader.hpp"
#include "ShaderInputSlot.hpp"
#include "ShaderUniformSlot.hpp"
#include "ShaderUniformValue.hpp"
#include "ShaderSpec.hpp"
#include "OpenGL.h"
#include <iostream>

namespace PlushGraphics {
    Shader::Shader(ShaderSpec spec)
    : identifier(spec.shaderName())
    {
        // obtain source code from ShaderSpec
        std::string vertexShaderSourceString = spec.vertexShaderSource();
        std::string fragmentShaderSourceString = spec.fragmentShaderSource();

        const char* vertexShaderSource = vertexShaderSourceString.c_str();
        const char* fragmentShaderSource = fragmentShaderSourceString.c_str();


        // compile shader from source
        shaderObjectReferenceID vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        checkCompileErrors(vertexShader, "VERTEX");

        shaderObjectReferenceID fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        checkCompileErrors(fragmentShader, "FRAGMENT");
        
        // create shader program
        shaderProgramID = glCreateProgram();
        glAttachShader(shaderProgramID, vertexShader);
        glAttachShader(shaderProgramID, fragmentShader);
        glLinkProgram(shaderProgramID);

        checkCompileErrors(shaderProgramID, "PROGRAM");

        // delete shaders used to create full shader program
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // load slot information from ShaderSpec
        uniformSlotIdentifiers = spec.shaderUniformSlotIdentifiers();
        inputSlots = spec.shaderInputSlots();

        for(ShaderMetadata::ShaderUniformSlotIdentifier slotIdentifier : uniformSlotIdentifiers){
            uniformSlotIndexMap[slotIdentifier] = uniformSlots.size();

            int location = glGetUniformLocation(shaderProgramID, slotIdentifier.getSlotName().c_str());
            if(location < 0){
                // uniform not in program or unused
                std::cout << "Warning: Uniform " << slotIdentifier.getSlotName() << 
                    " not present or unused in shader program " << identifier.getShaderName() << std::endl;
            }
            uniformSlots.push_back(ShaderMetadata::ShaderUniformSlot(slotIdentifier, (shaderSlotLocation_t)location));
        }

        // shader creation done
    }

    Shader::~Shader(){
        // delete shader program
        glDeleteProgram(shaderProgramID);
    }

    void Shader::useShader() {
        glUseProgram(shaderProgramID);
    }

    void Shader::setUniform(ShaderMetadata::ShaderUniformValue value) {
        useShader();

        value.setUniformAtLocation(getUniformSlotLocation(value.getTargetSlotIdentifier()));
    }

    shaderSlotLocation_t Shader::getUniformSlotLocation(ShaderMetadata::ShaderUniformSlotIdentifier identifier) {
        // return uniformSlots[uniformSlotIndexMap[identifier]].getLocation();
    }

    void Shader::checkCompileErrors(unsigned int shader, std::string type){
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
}