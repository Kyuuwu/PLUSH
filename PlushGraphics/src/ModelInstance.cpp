#include "ModelInstance.hpp"
#include "ModelInstanceIdentifier.hpp"
#include "ModelInstanceSpec.hpp"
#include "ManagedShader.hpp"
#include "ManagedModelData.hpp"
#include "OpenGL_Type.hpp"
#include "PlushGraphicsException.hpp"
#include "ModelVertex.hpp"
#include "PlushGraphicsOpenGL.hpp"

PlushGraphics::ModelInstance::ModelInstance(ModelInstanceSpec spec)
    : modelData(spec.getModelData()), shader(spec.getShader()), identifier(spec)
{
    // get list of shader inputs
    std::vector<ShaderMetadata::ShaderInputSlot> inputs = shader.getInputSlots();

    // get targeted slots from model data 
    std::vector<ShaderMetadata::ShaderInputSlotIdentifier> targetedInputSlots = modelData.getTargetedInputSlots();
    
    // check compatibility
    for(ShaderMetadata::ShaderInputSlot input : inputs){
        bool satisfied = false;
        for(ShaderMetadata::ShaderInputSlotIdentifier target : targetedInputSlots){
            if (target == input.getIdentifier()){
                if(satisfied){
                    throw(PlushGraphicsException::MODELDATA_HAS_DUPLICATE_TARGET_SLOT);
                }
                satisfied = true;
            }
        }
        if(!satisfied){
            throw(PlushGraphicsException::SHADER_AND_MODELDATA_INCOMPATIBLE);
        }
    }

    // load vertex data
    std::vector<ModelVertex> vertices = modelData.getVertices();
    numVertices = vertices.size();

    // generate vertex array object and buffer objects
    bufferReferenceID VAO;
    glGenVertexArrays(1, &VAO);
    VAO_map[GlobalGraphicsState::getActiveWindowIdentifier()] = VAO;

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind objects
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // calculate expected size of vertexdata
    size_t sizePerVertex = 0;
    for(ShaderMetadata::ShaderInputSlot input : inputs){
        sizePerVertex += getSizeOf(input.getIdentifier().getSlotType());
    }

    size_t totalSize = sizePerVertex * vertices.size();

    // std::cout << "Size per vertex: " << sizePerVertex << " bytes" << std::endl;
    // std::cout << "Total size: " << totalSize << " bytes" << std::endl;

    // fill in VBO buffer with empty data of appropriate size
    glBufferData(GL_ARRAY_BUFFER, totalSize, NULL, GL_STATIC_DRAW);

    loadVertexDataIntoBuffersAndSetupVertexAttributes(true, vertices);

    // get indices
    std::vector<size_t> indices = modelData.getIndices();
    // convert to GLuint in case of size issues
    std::vector<GLuint> indices_gluint;
    for(size_t index : indices){
        indices_gluint.push_back(index);
    }
    // set number of indices
    numIndices = indices.size();

    // read indices into EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indices_gluint.size(), &indices_gluint[0], GL_STATIC_DRAW);

    // unbind VBO but not EBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // not strictly necessary, but unbind VAO
    glBindVertexArray(0);
}

PlushGraphics::ModelInstance::~ModelInstance()
{
    // delete VAOs, VBO, and EBO

    for(auto& [windowID, VAO] : VAO_map){
        glDeleteVertexArrays(1, &VAO);
    }
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void PlushGraphics::ModelInstance::draw() {
    shader.useShader();

    if(VAO_map.count(GlobalGraphicsState::getActiveWindowIdentifier()) == 0){
        setUpNewVAO();
    }

    glBindVertexArray(VAO_map[GlobalGraphicsState::getActiveWindowIdentifier()]);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0);
}

void PlushGraphics::ModelInstance::setUpNewVAO() {
    
    // generate vertex array object and buffer objects
    bufferReferenceID VAO;
    glGenVertexArrays(1, &VAO);

    VAO_map[GlobalGraphicsState::getActiveWindowIdentifier()] = VAO;

    // bind objects
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    loadVertexDataIntoBuffersAndSetupVertexAttributes(false);

    // read indices into EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // unbind VBO but not EBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // not strictly necessary, but unbind VAO
    glBindVertexArray(0);
}

void PlushGraphics::ModelInstance::loadVertexDataIntoBuffersAndSetupVertexAttributes(bool loadVertexData, std::vector<ModelVertex> vertices) {
    // get list of shader inputs
    std::vector<ShaderMetadata::ShaderInputSlot> inputs = shader.getInputSlots();

    // get targeted slots from model data 
    std::vector<ShaderMetadata::ShaderInputSlotIdentifier> targetedInputSlots = modelData.getTargetedInputSlots();

    // extract vertex data into subsections of buffer and set vertex attributes

    size_t bufferPosition = 0;

    for(ShaderMetadata::ShaderInputSlot input : inputs){ 
        size_t targetIndex;

        if(loadVertexData){
            for(size_t i = 0; i < targetedInputSlots.size(); i++){
                if (targetedInputSlots[i] == input.getIdentifier()){
                    targetIndex = i;
                    break;
                }
            }
        }

        switch (input.getIdentifier().getSlotType()){
            case OpenGL_Type::UINT:{
                size_t valueSize = getSizeOf(OpenGL_Type::UINT);
                size_t subDataSize = valueSize*numVertices;

                if(loadVertexData){
                    std::vector<GLuint> values;
                    for(const ModelVertex& vertex : vertices){
                        values.push_back(vertex.vertexValues[targetIndex].get_uint());
                    }
                    glBufferSubData(GL_ARRAY_BUFFER, bufferPosition, subDataSize, &values[0]);
                }

                glVertexAttribPointer(input.getLocation(), 1, GL_UNSIGNED_INT, GL_FALSE, valueSize, (void*)bufferPosition);
                bufferPosition += subDataSize;
            }
            break;

            case OpenGL_Type::INT:{
                size_t valueSize = getSizeOf(OpenGL_Type::INT);
                size_t subDataSize = valueSize*numVertices;

                if(loadVertexData){
                    std::vector<GLint> values;
                    for(const ModelVertex& vertex : vertices){
                        values.push_back(vertex.vertexValues[targetIndex].get_int());
                    }
                    glBufferSubData(GL_ARRAY_BUFFER, bufferPosition, subDataSize, &values[0]);
                }

                glVertexAttribPointer(input.getLocation(), 1, GL_INT, GL_FALSE, valueSize, (void*)bufferPosition);
                bufferPosition += subDataSize;
            }
            break;
            
            case OpenGL_Type::FLOAT:{
                size_t valueSize = getSizeOf(OpenGL_Type::FLOAT);
                size_t subDataSize = valueSize*numVertices;

                if(loadVertexData){
                    std::vector<GLfloat> values;
                    for(const ModelVertex& vertex : vertices){
                        values.push_back(vertex.vertexValues[targetIndex].get_float());
                    }
                    glBufferSubData(GL_ARRAY_BUFFER, bufferPosition, subDataSize, &values[0]);
                }
                glVertexAttribPointer(input.getLocation(), 1, GL_FLOAT, GL_FALSE, valueSize, (void*)bufferPosition);
                bufferPosition += subDataSize;
            }
            break;
            
            case OpenGL_Type::FLOAT_VEC_2:{
                size_t valueSize = getSizeOf(OpenGL_Type::FLOAT);
                size_t subDataSize = 2*valueSize*numVertices;

                if(loadVertexData){
                    std::vector<GLfloat> values;
                    for(const ModelVertex& vertex : vertices){
                        values.push_back(vertex.vertexValues[targetIndex].get_vec2_subvalue(0));
                        values.push_back(vertex.vertexValues[targetIndex].get_vec2_subvalue(1));
                    }
                    glBufferSubData(GL_ARRAY_BUFFER, bufferPosition, subDataSize, &values[0]);
                }

                glVertexAttribPointer(input.getLocation(), 2, GL_FLOAT, GL_FALSE, 2*valueSize, (void*)bufferPosition);
                bufferPosition += subDataSize;
            }
            break;
            
            case OpenGL_Type::FLOAT_VEC_3:{
                size_t valueSize = getSizeOf(OpenGL_Type::FLOAT);
                size_t subDataSize = 3*valueSize*numVertices;

                if(loadVertexData){
                    std::vector<GLfloat> values;
                    for(const ModelVertex& vertex : vertices){
                        values.push_back(vertex.vertexValues[targetIndex].get_vec3_subvalue(0));
                        values.push_back(vertex.vertexValues[targetIndex].get_vec3_subvalue(1));
                        values.push_back(vertex.vertexValues[targetIndex].get_vec3_subvalue(2));
                    }
                    glBufferSubData(GL_ARRAY_BUFFER, bufferPosition, subDataSize, &values[0]);
                }
                glVertexAttribPointer(input.getLocation(), 3, GL_FLOAT, GL_FALSE, 3*valueSize, (void*)bufferPosition);
                bufferPosition += subDataSize;
            }
            break;
            
            case OpenGL_Type::FLOAT_VEC_4:{
                size_t valueSize = getSizeOf(OpenGL_Type::FLOAT);
                size_t subDataSize = 4*valueSize*numVertices;
                if(loadVertexData){
                    std::vector<GLfloat> values;
                    for(const ModelVertex& vertex : vertices){
                        values.push_back(vertex.vertexValues[targetIndex].get_vec4_subvalue(0));
                        values.push_back(vertex.vertexValues[targetIndex].get_vec4_subvalue(1));
                        values.push_back(vertex.vertexValues[targetIndex].get_vec4_subvalue(2));
                        values.push_back(vertex.vertexValues[targetIndex].get_vec4_subvalue(3));
                    }
                    glBufferSubData(GL_ARRAY_BUFFER, bufferPosition, subDataSize, &values[0]);
                }
                glVertexAttribPointer(input.getLocation(), 4, GL_FLOAT, GL_FALSE, 4*valueSize, (void*)bufferPosition);
                bufferPosition += subDataSize;
            }
            break;
            
            default:{
                std::cout << "ModelInstance construction for " << getStringFromType(input.getIdentifier().getSlotType()) << " not supported yet." << std::endl;
                throw(PlushGraphicsException::OPENGL_TYPE_NOT_FOUND);
            }


        }

        glEnableVertexAttribArray(input.getLocation()); // enable vertex attribute
    }
}

