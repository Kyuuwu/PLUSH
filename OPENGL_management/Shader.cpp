#include "OPENGL_management_includes.h"
#include "OPENGL_includes.h"

#include "Exceptions.h"

#include <filesystem>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


namespace OPENGL_management {
    std::vector<ShaderInput> Shader::getInputs(){
        return inputs;
    }

    std::vector<ShaderUniformSlot> Shader::getUniformSlots(){
        return uniforms;
    }

    void Shader::generateInputs(std::string vertexInputPath){
        std::ifstream inputfile;
        std::stringstream shaderinputstream;
        try 
        {
            // open files
            inputfile.open(vertexInputPath);
            // read file's buffer contents into streams
            shaderinputstream << inputfile.rdbuf();
            // close file handlers
            inputfile.close();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
            throw(PLUSH_helpers::FILE_READ_ERROR);
        }

        unsigned int position;
        std::string type;
        std::string name;

        unsigned int inputcount;

        shaderinputstream >> inputcount;

        for(int i = 0; i < inputcount; i++){
            shaderinputstream >> position;
            shaderinputstream >> type;
            shaderinputstream >> name;

            ShaderInput input;
            input.location = position;
            input.name = name;
            input.type = getTypeFromString(type);

            inputs.push_back(input);
        }

        if(!shaderinputstream){
            throw(PLUSH_helpers::FILE_INCOMPLETE);
        }
    }

    void Shader::use(){
        if(beingUsed){
            return;
        }

        glUseProgram(ShaderID);
    }

    ShaderUniformSlot Shader::getSlotForTarget(ShaderUniformTarget target){
        for (ShaderUniformSlot s : uniforms){
            if (s.name == target.name && s.type == target.type){
                return s;
            }
        }
        throw(MATCHING_UNIFORM_SLOT_NOT_FOUND);
    }

    int Shader::getSlotIndexForTarget(ShaderUniformTarget &target){
        for (int i = 0; i < uniforms.size(); i++){
            if (uniforms[i].type == target.type && uniforms[i].name == target.name){
                return i;
            }
        }

        return -1;
    }
    
    void Shader::addSlot(ShaderUniformSlot slot)
    {
        for(ShaderUniformSlot existingslot : uniforms){
            if(slot.name == existingslot.name && slot.location == existingslot.location){
                return; // TODO: IMPLEMENT MORE CAREFUL CHECKS FOR OVERLAP AND STUFF
            }
        }

        uniforms.push_back(slot);
    }

    void Shader::setBeingUsed(bool value){
        beingUsed = value;
    }

    void Shader::setUniform(ShaderUniformValue &value, ShaderUniformTarget &target){
        int index = getSlotIndexForTarget(target);
        
        if (index == -1){
            // std::cout << "Failed to find matching uniform. Uniform name: " << target.name << std::endl;
            // throw(MATCHING_UNIFORM_SLOT_NOT_FOUND);
            return;
        }

        setUniform(value, index);


        // try{
        //     setUniform(value, getSlotForTarget(target));
        // } catch(Exception e){
        //     if (e == MATCHING_UNIFORM_SLOT_NOT_FOUND){
        //         std::cout << "Uniform slot " << target.name << " not found in shader " << name << ", ignoring setUniform command" << std::endl;
        //     } else {
        //         throw(PLUSH_helpers::UNEXPECTED_EXCEPTION);
        //     }
        // }
    }

    void Shader::setUniform(ShaderUniformValue &value, ShaderUniformSlot &uniform){
        for(size_t i = 0 ; i < uniforms.size(); i++){
            if (isSameSlot(uniforms[i], uniform)){
                setUniform(value, i);
            }
        }
    }

    void Shader::setUniform(ShaderUniform &uniform)
    {
        setUniform(uniform.value, uniform.target);
    }

    void Shader::setUniform(ShaderUniformValue &value, int index){
        use();
        switch(uniforms[index].type){
            case OPENGL_INT:
                glUniform1i(uniforms[index].location, value.i);
                break;

            case OPENGL_UINT:
                glUniform1ui(uniforms[index].location, value.u);
                break;

            case OPENGL_FLOAT:
                glUniform1f(uniforms[index].location, value.f);
                break;

            case OPENGL_FLOAT_VEC_2:
                glUniform2fv(uniforms[index].location, 1, (GLfloat*)value.fptr);
                break;

            case OPENGL_FLOAT_VEC_3:
                glUniform3fv(uniforms[index].location, 1, (GLfloat*)value.fptr);
                break;

            case OPENGL_FLOAT_VEC_4:
                glUniform4fv(uniforms[index].location, 1, (GLfloat*)value.fptr);
                break;

            case OPENGL_FLOAT_MAT_2:
                glUniformMatrix2fv(uniforms[index].location, 1, false, (GLfloat*)value.fptr);
                break;

            case OPENGL_FLOAT_MAT_3:
                glUniformMatrix3fv(uniforms[index].location, 1, false, (GLfloat*)value.fptr);
                break;

            case OPENGL_FLOAT_MAT_4:
                glUniformMatrix4fv(uniforms[index].location, 1, false, (GLfloat*)value.fptr);
                break;

            case OPENGL_SAMPLER2D:
                glUniform1i(uniforms[index].location, value.i);
                break;

            default:
                std::cout << "Invalid uniform type. Type code: " << (int) uniforms[index].type << ", name: " << uniforms[index].name << std::endl;
                throw(INVALID_UNIFORM_TYPE);
        }

        uniforms[index].isSet = true;
    }

    Shader::Shader(const char* vertexPath, const char* fragmentPath, const char *name){
        this->name = name;

        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
            throw(PLUSH_helpers::FILE_READ_ERROR);
        }

        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;

        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        unsigned int ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        ShaderID = ID;

        std::string vertexpathstring(vertexPath);
        std::string fragmentpathstring(fragmentPath);

        std::string vertexinputpath = vertexpathstring + ".input";

        generateInputs(vertexinputpath);

        std::string vertexuniformpath = vertexpathstring + ".uniforms";
        std::string fragmentuniformpath = fragmentpathstring + ".uniforms";

        try{
            addUniformSlots(vertexuniformpath);
            addUniformSlots(fragmentuniformpath);
        } catch (Exception e){
            switch(e){
                case SHADER_COMPILE_MISSING_UNIFORM_SLOT:
                    std::cout << "Missing uniform slot." << std::endl;
                    break;
                    // throw(e);

                case INVALID_DEFAULT_CODE:
                    std::cout << "Invalid default code." << std::endl;
                    throw(e);

                case INVALID_UNIFORM_TYPE:
                    std::cout << "Invalid uniform type." << std::endl;
                    throw(e);

                default:
                    std::cout << "Other error" << std::endl;
                    throw(e);
            }
        }
    }

    void Shader::addUniformSlots(std::string path){  // ADD CODE FOR DEFAULT/INITIAL VALUES
        std::ifstream uniformFile;
        std::stringstream uniformStream;
        try 
        {
            // open files
            uniformFile.open(path);
            // read file's buffer contents into streams
            uniformStream << uniformFile.rdbuf();
            // close file handlers
            uniformFile.close();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::MODEL::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
            throw(PLUSH_helpers::FILE_READ_ERROR); 
        }

        unsigned int num_uniforms;

        uniformStream >> num_uniforms;

        if(!uniformStream){
            throw(PLUSH_helpers::FILE_INCOMPLETE);
        }

        std::string slot_type;
        size_t policy;

        for(int i = 0; i < num_uniforms ; i++){
            ShaderUniformSlot slot;
            uniformStream >> slot_type;
            slot.type = getTypeFromString(slot_type);
            uniformStream >> slot.name;

            switch(slot.type){
                case OPENGL_FLOAT:{
                    float defaultValue;
                    uniformStream >> defaultValue;
                    slot.defaultValue.f = defaultValue;
                    break;
                }
                case OPENGL_UINT:{
                    unsigned int defaultValue;
                    uniformStream >> defaultValue;
                    slot.defaultValue.u = defaultValue;
                    break;
                }
                case OPENGL_INT:{
                    int defaultValue;
                    uniformStream >> defaultValue;
                    slot.defaultValue.i = defaultValue;
                    break;
                }
                default:{
                    int defaultCode = 0;
                    uniformStream >> defaultCode;
                    slot.defaultValue = ShaderUniformDefaults::getDefaultValue(slot.type, defaultCode);
                }
            }

            uniformStream >> policy;
            slot.check_policy = (SlotSetCheckPolicy) policy;

            slot.location = glGetUniformLocation(ShaderID, slot.name.c_str());

            if(slot.location == -1){
                throw(SHADER_COMPILE_MISSING_UNIFORM_SLOT);
            }

            addSlot(slot);
        }

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

    unsigned int Shader::getID(){
        return ShaderID;
    }

    std::string getFragmentShaderPath(std::string filename){
        return std::filesystem::current_path().string()+"/shaders/fragment/"+filename;
    }

    std::string getVertexShaderPath(std::string filename){
        return std::filesystem::current_path().string()+"/shaders/vertex/"+filename;
    }

    std::string getComboShaderPath(std::string filename){
        return std::filesystem::current_path().string()+"/shaders/combo/"+filename;
    }

    std::string Shader::getName(){
        return name;
    }

    void Shader::resetAllUniformSetChecks(){
        // std::cout << "Reset called" << std::endl;

        for (int i = 0; i < uniforms.size(); i++){
            uniforms.at(i).isSet = false;
        }
    }
    
    void Shader::resetPerLayerUniformSetChecks()
    {
        for (int i = 0; i < uniforms.size(); i++){
            if(uniforms[i].check_policy == RESET_PER_LAYER){
                uniforms[i].isSet = false;
            }
        }
    }
    
    void Shader::resetPerInstanceUniformSetChecks()
    {
        for (int i = 0; i < uniforms.size(); i++){
            if(uniforms[i].check_policy == RESET_PER_INSTANCE){
                uniforms[i].isSet = false;
            }
        }
    }

    void Shader::setUnsetUniformsToDefault(){
        for(ShaderUniformSlot slot: uniforms){
            if(!slot.isSet){

                std::cout << "Uniform " << slot.name << " was not set." << std::endl;
                setUniform(slot.defaultValue, slot);
            }
        }
    }
    
    void Shader::DEBUG_LIST_UNIFORM_SLOTS()
    {
        for(ShaderUniformSlot slot : uniforms){
            std::cout << "Shader name: " << slot.name << std::endl;
            std::cout << "Shader check policy: " << slot.check_policy << std::endl;
            std::cout << "Shader location: " << slot.location << std::endl<<std::endl;
        }
    }
}