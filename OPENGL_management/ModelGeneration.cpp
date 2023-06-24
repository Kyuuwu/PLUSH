#include "OPENGL_includes.h"
#include "OPENGL_management_includes.h"

#include "Exceptions.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace OPENGL_management {
    unsigned int ModelGeneration::getVertexValueCount(std::vector<ShaderInput> inputs){
        unsigned int count = 0;

        for(ShaderInput input: inputs){
            count += getInputValueCount(input);
        }
        return count;
    }

    unsigned int ModelGeneration::getInputValueCount(ShaderInput input){

        switch(input.type){
            case OPENGL_INT:
                return 1;
                break;

            case OPENGL_UINT:
                return 1;
                break;

            case OPENGL_FLOAT:
                return 1;
                break;

            case OPENGL_FLOAT_VEC_2:
                return 2;
                break;

            case OPENGL_FLOAT_VEC_3:
                return 3;
                break;

            case OPENGL_FLOAT_VEC_4:
                return 4;
                break;

            default:
                throw(INVALID_INPUT_TYPE);
            
        }
    }

    GLenum getGLenumFromType(GL_type type){
        switch(type){
            case OPENGL_INT:
                return GL_INT;
            
            case OPENGL_UINT:
                return GL_UNSIGNED_INT;

            case OPENGL_FLOAT:
            case OPENGL_FLOAT_VEC_2:
            case OPENGL_FLOAT_VEC_3:
            case OPENGL_FLOAT_VEC_4:
                return GL_FLOAT;
            
            default:
                throw(INVALID_TYPE);
        }
    }

    Model* ModelGeneration::createModel(std::string name, VertexHolder holder){
        unsigned int num_vertex_values_per_vertex = getVertexValueCount(holder.inputs);
        unsigned int num_vertex_values = holder.vertices.size();
        unsigned int num_vertices = num_vertex_values / num_vertex_values_per_vertex;

        unsigned int VAO, VBO;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, num_vertex_values*sizeof(VertexValue), &holder.vertices[0], GL_STATIC_DRAW);

        unsigned int offset = 0;

        for(ShaderInput input : holder.inputs){
            GLenum type = getGLenumFromType(input.type);

            glVertexAttribPointer(input.location, getInputValueCount(input), type, GL_FALSE, num_vertex_values_per_vertex*sizeof(VertexValue), (void*) (offset*sizeof(VertexValue)));
            glEnableVertexAttribArray(input.location);

            offset += getInputValueCount(input);
        }

        Model* model = new Model(name, VAO, VBO, num_vertices, holder.inputs);

        return model;
    }

    Model* ModelGeneration::createModel(std::string name, VertexHolder holder, std::vector<unsigned int> indices){
        unsigned int num_vertex_values_per_vertex = getVertexValueCount(holder.inputs);
        unsigned int num_vertex_values = holder.vertices.size();

        unsigned int num_indices = indices.size();

        unsigned int VAO, VBO, EBO;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, num_vertex_values*sizeof(VertexValue), &holder.vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        unsigned int offset = 0;

        for(ShaderInput input : holder.inputs){
            GLenum type = getGLenumFromType(input.type);

            glVertexAttribPointer(input.location, getInputValueCount(input), type, GL_FALSE, num_vertex_values_per_vertex*sizeof(VertexValue), (void*) (offset*sizeof(VertexValue)));
            glEnableVertexAttribArray(input.location);

            offset += getInputValueCount(input);
        }

        Model* model = new Model(name, VAO, VBO, EBO, num_indices, holder.inputs);

        return model;
    }

    VertexHolder ModelGeneration::loadModelFromFile_Basic(std::string path){
        std::ifstream modelfile;
        std::stringstream modelstream;
        try 
        {
            // open files
            modelfile.open(path);
            // read file's buffer contents into streams
            modelstream << modelfile.rdbuf();
            // close file handlers
            modelfile.close();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::MODEL::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
            throw(PLUSH_helpers::FILE_READ_ERROR); 
        }

        unsigned int num_vertex_values, num_inputs;

        modelstream >> num_vertex_values;
        modelstream >> num_inputs;

        if(!modelstream){
            throw(PLUSH_helpers::FILE_INCOMPLETE);
        }

        std::vector<ShaderInput> inputs;

        unsigned int location;
        std::string name;
        std::string typestring;

        for (int i = 0; i < num_inputs; i++){
            modelstream >> location;
            modelstream >> typestring;
            modelstream >> name;

            ShaderInput input;
            input.location = location;
            input.name = name;
            
            input.type = getTypeFromString(typestring);

            inputs.push_back(input);
        }

        if(!modelstream){
            throw(PLUSH_helpers::FILE_INCOMPLETE);
        }

        float value;

        std::vector<VertexValue> vertices;

        for(int i = 0; i < num_vertex_values; i++){
            VertexValue value;
            for(ShaderInput input : inputs){
                switch(input.type){
                    case OPENGL_INT:
                        modelstream >> value.i;
                        vertices.push_back(value);
                        break;

                    case OPENGL_UINT:
                        modelstream >> value.u;
                        vertices.push_back(value);
                        break;

                    case OPENGL_FLOAT:
                        modelstream >> value.f;
                        vertices.push_back(value);
                        break;

                    case OPENGL_FLOAT_VEC_2:
                        modelstream >> value.f;
                        vertices.push_back(value);
                        modelstream >> value.f;
                        vertices.push_back(value);
                        break;

                    case OPENGL_FLOAT_VEC_3:
                        modelstream >> value.f;
                        vertices.push_back(value);
                        modelstream >> value.f;
                        vertices.push_back(value);
                        modelstream >> value.f;
                        vertices.push_back(value);
                        break;

                    case OPENGL_FLOAT_VEC_4:
                        modelstream >> value.f;
                        vertices.push_back(value);
                        modelstream >> value.f;
                        vertices.push_back(value);
                        modelstream >> value.f;
                        vertices.push_back(value);
                        modelstream >> value.f;
                        vertices.push_back(value);
                        break;

                    default:
                        throw(INVALID_INPUT_TYPE);
                }
            }

            if(!modelstream){
                throw(PLUSH_helpers::FILE_INCOMPLETE);
            }
        }

        VertexHolder holder;
        holder.vertices = vertices;
        holder.inputs = inputs;

        return holder;
    }

    Model* ModelGeneration::createModelFromFile_Basic(std::string path){
        VertexHolder holder = loadModelFromFile_Basic(getModelPath_Basic(path));
        return createModel(path, holder);
    }

    std::string getModelPath_Basic(std::string modelname){
        return std::filesystem::current_path().string()+"/models/basic/"+modelname;
    }

    std::string getModelPath_Basic_EBO(std::string modelname){
        return std::filesystem::current_path().string()+"/models/basic_EBO/"+modelname;
    }

    std::vector<unsigned int> ModelGeneration::loadIndicesFromFile_Basic(std::string path){
        std::ifstream indexfile;
        std::stringstream indexstream;
        try 
        {
            // open files
            indexfile.open(path);
            // read file's buffer contents into streams
            indexstream << indexfile.rdbuf();
            // close file handlers
            indexfile.close();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::MODEL::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
            throw(PLUSH_helpers::FILE_READ_ERROR); 
        }

        unsigned int num_indices;

        indexstream >> num_indices;

        if(!indexstream){
            throw(PLUSH_helpers::FILE_INCOMPLETE);
        }

        std::vector<unsigned int> indices;

        unsigned int index;

        for(int i = 0 ; i < num_indices ; i++){
            indexstream >> index;
            indices.push_back(index);
        }

        if(!indexstream){
            throw(PLUSH_helpers::FILE_INCOMPLETE);
        }

        return indices;
    }

    Model* ModelGeneration::createModelFromFile_Basic_EBO(std::string path){
        std::string vertexpath = getModelPath_Basic_EBO(path);
        std::string indexpath = vertexpath + ".index";

        VertexHolder holder = loadModelFromFile_Basic(vertexpath);

        std::vector<unsigned int> indices = loadIndicesFromFile_Basic(indexpath);

        return createModel(path,holder, indices);
    }
}