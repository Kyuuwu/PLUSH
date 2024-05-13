#include "OPENGL_management_includes.h"
#include "OPENGL_includes.h"

#include "Exceptions.h"
#include "Helpers.h"

#include <filesystem>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


namespace OPENGL_management {

    // void Shader::generateInputs(std::string vertexInputPath){
    //     std::ifstream inputfile;
    //     std::stringstream shaderinputstream;
    //     try 
    //     {
    //         // open files
    //         inputfile.open(vertexInputPath);
    //         // read file's buffer contents into streams
    //         shaderinputstream << inputfile.rdbuf();
    //         // close file handlers
    //         inputfile.close();
    //     }
    //     catch (std::ifstream::failure& e)
    //     {
    //         std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    //         throw(PLUSH_helpers::FILE_READ_ERROR);
    //     }

    //     unsigned int position;
    //     std::string type;
    //     std::string name;

    //     unsigned int inputcount;

    //     shaderinputstream >> inputcount;

    //     for(int i = 0; i < inputcount; i++){
    //         shaderinputstream >> position;
    //         shaderinputstream >> type;
    //         shaderinputstream >> name;

    //         ShaderInput input;
    //         input.location = position;
    //         input.name = name;
    //         input.type = getTypeFromString(type);

    //         inputs.push_back(input);
    //     }

    //     if(!shaderinputstream){
    //         throw(PLUSH_helpers::FILE_INCOMPLETE);
    //     }
    // }

    ShaderUniformSlot Shader::getSlotForTarget(ShaderUniformTarget target){
        for (ShaderUniformSlot s : uniform_slots){
            if (s.name == target.name && s.type == target.type){
                return s;
            }
        }
        throw(MATCHING_UNIFORM_SLOT_NOT_FOUND);
    }

    int Shader::getSlotIndexForTarget(ShaderUniformTarget &target){
        for (int i = 0; i < uniform_slots.size(); i++){
            if (uniform_slots[i].type == target.type && uniform_slots[i].name == target.name){
                return i;
            }
        }

        return -1;
    }
    
    void Shader::generateTargetList()
    {
        uniform_targets.clear();
        for (ShaderUniformSlot slot : uniform_slots){
            ShaderUniformTarget target;
            target.name = slot.name;
            target.type = slot.type;

            uniform_targets.push_back(target);
        }
    }

    // void Shader::setBeingUsed(bool value){
    //     beingUsed = value;
    // }

    // void Shader::setUniform(ShaderUniformValue &value, ShaderUniformSlot &uniform){
    //     for(size_t i = 0 ; i < uniform_slots.size(); i++){
    //         if (isSameSlot(uniform_slots[i], uniform)){
    //             setUniform(value, i);
    //         }
    //     }
    // }

    // Shader::Shader(const char* vertexPath, const char* fragmentPath, const char *name){
    //     this->name = name;

    //     // 1. retrieve the vertex/fragment source code from filePath
    //     std::string vertexCode;
    //     std::string fragmentCode;
    //     std::ifstream vShaderFile;
    //     std::ifstream fShaderFile;
    //     // ensure ifstream objects can throw exceptions:
    //     vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    //     fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    //     try 
    //     {
    //         // open files
    //         vShaderFile.open(vertexPath);
    //         fShaderFile.open(fragmentPath);
    //         std::stringstream vShaderStream, fShaderStream;
    //         // read file's buffer contents into streams
    //         vShaderStream << vShaderFile.rdbuf();
    //         fShaderStream << fShaderFile.rdbuf();
    //         // close file handlers
    //         vShaderFile.close();
    //         fShaderFile.close();
    //         // convert stream into string
    //         vertexCode   = vShaderStream.str();
    //         fragmentCode = fShaderStream.str();
    //     }
    //     catch (std::ifstream::failure& e)
    //     {
    //         std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    //         throw(PLUSH_helpers::FILE_READ_ERROR);
    //     }

    //     const char* vShaderCode = vertexCode.c_str();
    //     const char * fShaderCode = fragmentCode.c_str();
    //     // 2. compile shaders
    //     unsigned int vertex, fragment;

    //     // vertex shader
    //     vertex = glCreateShader(GL_VERTEX_SHADER);

    //     glShaderSource(vertex, 1, &vShaderCode, NULL);
    //     glCompileShader(vertex);
    //     checkCompileErrors(vertex, "VERTEX");

    //     // fragment Shader
    //     fragment = glCreateShader(GL_FRAGMENT_SHADER);

    //     glShaderSource(fragment, 1, &fShaderCode, NULL);
    //     glCompileShader(fragment);
        
    //     checkCompileErrors(fragment, "FRAGMENT");
    //     // shader Program
    //     unsigned int ID = glCreateProgram();
    //     glAttachShader(ID, vertex);
    //     glAttachShader(ID, fragment);
    //     glLinkProgram(ID);
    //     checkCompileErrors(ID, "PROGRAM");
    //     // delete the shaders as they're linked into our program now and no longer necessary
    //     glDeleteShader(vertex);
    //     glDeleteShader(fragment);

    //     ShaderID = ID;

    //     std::string vertexpathstring(vertexPath);
    //     std::string fragmentpathstring(fragmentPath);

    //     std::string vertexinputpath = vertexpathstring + ".input";

    //     generateInputs(vertexinputpath);

    //     std::string vertexuniformpath = vertexpathstring + ".uniforms";
    //     std::string fragmentuniformpath = fragmentpathstring + ".uniforms";

    //     try{
    //         addUniformSlots(vertexuniformpath);
    //         addUniformSlots(fragmentuniformpath);
    //     } catch (Exception e){
    //         switch(e){
    //             case SHADER_COMPILE_MISSING_UNIFORM_SLOT:
    //                 std::cout << "Missing uniform slot." << std::endl;
    //                 break;
    //                 // throw(e);

    //             case INVALID_DEFAULT_CODE:
    //                 std::cout << "Invalid default code." << std::endl;
    //                 throw(e);

    //             case INVALID_UNIFORM_TYPE:
    //                 std::cout << "Invalid uniform type." << std::endl;
    //                 throw(e);

    //             default:
    //                 std::cout << "Other error" << std::endl;
    //                 throw(e);
    //         }
    //     }
    // }

    // void Shader::addUniformSlots(std::string path){  // ADD CODE FOR DEFAULT/INITIAL VALUES
    //     std::ifstream uniformFile;
    //     std::stringstream uniformStream;
    //     try 
    //     {
    //         // open files
    //         uniformFile.open(path);
    //         // read file's buffer contents into streams
    //         uniformStream << uniformFile.rdbuf();
    //         // close file handlers
    //         uniformFile.close();
    //     }
    //     catch (std::ifstream::failure& e)
    //     {
    //         std::cout << "ERROR::MODEL::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    //         throw(PLUSH_helpers::FILE_READ_ERROR); 
    //     }

    //     unsigned int num_uniforms;

    //     uniformStream >> num_uniforms;

    //     if(!uniformStream){
    //         throw(PLUSH_helpers::FILE_INCOMPLETE);
    //     }

    //     std::string slot_type;
    //     size_t policy;

    //     for(int i = 0; i < num_uniforms ; i++){
    //         ShaderUniformSlot slot;
    //         uniformStream >> slot_type;
    //         slot.type = getTypeFromString(slot_type);
    //         uniformStream >> slot.name;

    //         switch(slot.type){
    //             case OPENGL_FLOAT:{
    //                 float defaultValue;
    //                 uniformStream >> defaultValue;
    //                 slot.defaultValue.f = defaultValue;
    //                 break;
    //             }
    //             case OPENGL_UINT:{
    //                 unsigned int defaultValue;
    //                 uniformStream >> defaultValue;
    //                 slot.defaultValue.u = defaultValue;
    //                 break;
    //             }
    //             case OPENGL_INT:{
    //                 int defaultValue;
    //                 uniformStream >> defaultValue;
    //                 slot.defaultValue.i = defaultValue;
    //                 break;
    //             }
    //             default:{
    //                 int defaultCode = 0;
    //                 uniformStream >> defaultCode;
    //                 slot.defaultValue = ShaderUniformDefaults::getDefaultValue(slot.type, defaultCode);
    //             }
    //         }

    //         uniformStream >> policy;
    //         slot.check_policy = (SlotSetCheckPolicy) policy;

    //         slot.location = glGetUniformLocation(ShaderID, slot.name.c_str());

    //         if(slot.location == -1){
    //             throw(SHADER_COMPILE_MISSING_UNIFORM_SLOT);
    //         }

    //         addSlot(slot);
    //     }

    // }

    std::string getFragmentShaderPath(std::string filename){
        return std::filesystem::current_path().string()+"/shaders/fragment/"+filename;
    }

    std::string getVertexShaderPath(std::string filename){
        return std::filesystem::current_path().string()+"/shaders/vertex/"+filename;
    }

    std::string getComboShaderPath(std::string filename){
        return std::filesystem::current_path().string()+"/shaders/combo/"+filename;
    }

    // void Shader::resetAllUniformSetChecks(){
    //     // std::cout << "Reset called" << std::endl;

    //     for (int i = 0; i < uniform_slots.size(); i++){
    //         uniform_slots.at(i).isSet = false;
    //     }
    // }
    
    // void Shader::resetPerLayerUniformSetChecks()
    // {
    //     for (int i = 0; i < uniform_slots.size(); i++){
    //         if(uniform_slots[i].check_policy == RESET_PER_LAYER){
    //             uniform_slots[i].isSet = false;
    //         }
    //     }
    // }
    
    // void Shader::resetPerInstanceUniformSetChecks()
    // {
    //     for (int i = 0; i < uniform_slots.size(); i++){
    //         if(uniform_slots[i].check_policy == RESET_PER_INSTANCE){
    //             uniform_slots[i].isSet = false;
    //         }
    //     }
    // }

    // void Shader::setUnsetUniformsToDefault(){
    //     for(ShaderUniformSlot slot: uniform_slots){
    //         if(!slot.isSet){

    //             std::cout << "Uniform " << slot.name << " was not set." << std::endl;
    //             setUniform(slot.defaultValue, slot);
    //         }
    //     }
    // }
    
    void Shader::DEBUG_LIST_UNIFORM_SLOTS()
    {
        for(ShaderUniformSlot slot : uniform_slots){
            std::cout << "Shader name: " << slot.name << std::endl;
            std::cout << "Shader check policy: " << slot.check_policy << std::endl;
            std::cout << "Shader location: " << slot.location << std::endl<<std::endl;
        }
    }


Shader::Shader(std::string comboPath)
    {
        std::stringstream combostream = PLUSH_helpers::getStreamFromFile(getComboShaderPath(comboPath));

        std::string shader_name, vertexPath, fragmentPath;

        combostream >> shader_name;
        combostream >> vertexPath;
        combostream >> fragmentPath;

        vertexPath = getVertexShaderPath(vertexPath);
        fragmentPath = getFragmentShaderPath(fragmentPath);

        // std::cout << vertexPath << " and " << fragmentPath << std::endl;

        if(!combostream){
            throw(PLUSH_helpers::FILE_INCOMPLETE);
        }

        this->name = shader_name;

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

        unsigned int input_position;
        std::string input_type;
        std::string input_name;

        unsigned int inputcount;

        combostream >> inputcount;

        for(int i = 0; i < inputcount; i++){
            combostream >> input_position;
            combostream >> input_type;
            combostream >> input_name;

            ShaderInput input;
            input.location = input_position;
            input.name = input_name;
            input.type = getTypeFromString(input_type);

            inputs.push_back(input);
        }

        if(!combostream){
            throw(PLUSH_helpers::FILE_INCOMPLETE);
        }

        uint32_t num_uniforms;

        combostream >> num_uniforms;

        if(!combostream){
            throw(PLUSH_helpers::FILE_INCOMPLETE);
        }

        std::string slot_type;
        size_t policy;

        for(int i = 0; i < num_uniforms ; i++){
            ShaderUniformSlot slot;
            combostream >> slot_type;
            slot.type = getTypeFromString(slot_type);
            combostream >> slot.name;

            switch(slot.type){
                case OPENGL_FLOAT:{
                    float defaultValue;
                    combostream >> defaultValue;
                    slot.defaultValue.f = defaultValue;
                    break;
                }
                case OPENGL_UINT:{
                    unsigned int defaultValue;
                    combostream >> defaultValue;
                    slot.defaultValue.u = defaultValue;
                    break;
                }
                case OPENGL_INT:{
                    int defaultValue;
                    combostream >> defaultValue;
                    slot.defaultValue.i = defaultValue;
                    break;
                }
                default:{
                    int defaultCode = 0;
                    combostream >> defaultCode;
                    slot.defaultValue = ShaderUniformDefaults::getDefaultValue(slot.type, defaultCode);
                }
            }

            // combostream >> policy;
            // slot.check_policy = (SlotSetCheckPolicy) policy;

            slot.location = glGetUniformLocation(ShaderID, slot.name.c_str());

            if(slot.location == -1){
                throw(SHADER_COMPILE_MISSING_UNIFORM_SLOT);
            }

            addSlot(slot);
        }
        generateTargetList();
        
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
    
    void Shader::addSlot(ShaderUniformSlot slot)
    {
        for(ShaderUniformSlot existingslot : uniform_slots){
            if(slot.name == existingslot.name && slot.location == existingslot.location){
                return; // TODO: IMPLEMENT MORE CAREFUL CHECKS FOR OVERLAP AND STUFF
            }
        }

        uniform_slots.push_back(slot);
    }

    void Shader::use(){
        glUseProgram(ShaderID);
    }

    void Shader::setUniform(ShaderUniform &uniform)
    {
        setUniform(uniform.value, uniform.target);
    }

    void Shader::setUniform(ShaderUniformValue &value, ShaderUniformTarget &target){
        int index = getSlotIndexForTarget(target);
        
        if (index == -1){
            // std::cout << "Failed to find matching uniform. Uniform name: " << target.name << std::endl;
            // throw(MATCHING_UNIFORM_SLOT_NOT_FOUND);
            return;
        }

        setUniform(value, index);
    }

    void Shader::setUniform(ShaderUniformValue &value, int index){
        use();
        switch(uniform_slots[index].type){
            case OPENGL_INT:
                glUniform1i(uniform_slots[index].location, value.i);
                break;

            case OPENGL_UINT:
                glUniform1ui(uniform_slots[index].location, value.u);
                break;

            case OPENGL_FLOAT:
                glUniform1f(uniform_slots[index].location, value.f);
                break;

            case OPENGL_FLOAT_VEC_2:
                glUniform2fv(uniform_slots[index].location, 1, (GLfloat*)value.fptr);
                break;

            case OPENGL_FLOAT_VEC_3:
                glUniform3fv(uniform_slots[index].location, 1, (GLfloat*)value.fptr);
                break;

            case OPENGL_FLOAT_VEC_4:
                glUniform4fv(uniform_slots[index].location, 1, (GLfloat*)value.fptr);
                break;

            case OPENGL_FLOAT_MAT_2:
                glUniformMatrix2fv(uniform_slots[index].location, 1, false, (GLfloat*)value.fptr);
                break;

            case OPENGL_FLOAT_MAT_3:
                glUniformMatrix3fv(uniform_slots[index].location, 1, false, (GLfloat*)value.fptr);
                break;

            case OPENGL_FLOAT_MAT_4:
                glUniformMatrix4fv(uniform_slots[index].location, 1, false, (GLfloat*)value.fptr);
                break;

            case OPENGL_SAMPLER2D:
                glUniform1i(uniform_slots[index].location, value.i);
                break;

            default:
                std::cout << "Invalid uniform type. Type code: " << (int) uniform_slots[index].type << ", name: " << uniform_slots[index].name << std::endl;
                throw(INVALID_UNIFORM_TYPE);
        }

        uniform_slots[index].isSet = true;
    }
    
    void Shader::setTexture2DUniform(TextureNamePair namepair, uint32_t textureunit)
    {
        Texture2D* textureptr = TextureLibrary::getTexture2DByName(namepair.texturename).get();
        
        textureptr->use(textureunit);

        ShaderUniform texture_uniform;
        texture_uniform.target.name = namepair.uniformname;
        texture_uniform.target.type = OPENGL_SAMPLER2D;
        texture_uniform.value.i = (int)textureunit;

        setUniform(texture_uniform);
    }

    std::vector<ShaderInput> Shader::getInputs(){
        return inputs;
    }

    std::vector<ShaderUniformSlot> Shader::getUniformSlots(){
        return uniform_slots;
    }
    
    std::vector<ShaderUniformTarget> Shader::getUniformTargets()
    {
        return uniform_targets;
    }

    unsigned int Shader::getID(){
        return ShaderID;
    }

    std::string Shader::getName(){
        return name;
    }

}