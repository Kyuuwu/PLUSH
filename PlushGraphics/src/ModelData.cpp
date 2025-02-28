#include "ModelData.hpp"
#include "ModelDataSpec.hpp"
#include "ModelVertex.hpp"
#include "ShaderInputSlotIdentifier.hpp"
#include "OpenGL_Type.hpp"
#include "ReadFile.hpp"
#include <sstream>
#include <iostream>
#include <vector>

namespace PlushGraphics {
    ModelData::ModelData(ModelDataSpec spec):
    identifier("temp"){
        std::stringstream modelstream = PlushUtil::ReadFile::readFileIntoStringStream("models/"+spec.getModelDataFileName());

        std::string modelDataName;
        modelstream >> modelDataName;
        identifier = ModelDataIdentifier(modelDataName);

        uint32_t inputCount;
        modelstream >> inputCount;

        // std::cout << "Input count: " << inputCount << std::endl;

        for (uint32_t i = 0; i < inputCount; i++) {
            std::string typeName;
            std::string varName;

            modelstream >> typeName;
            OpenGL_Type type = getTypeFromString(typeName);
            modelstream >> varName;

            ShaderMetadata::ShaderInputSlotIdentifier identifier(varName, type);
            targetedInputSlots.push_back(identifier);
        }

        uint32_t vertexCount;
        modelstream >> vertexCount;

        // std::cout << "Vertex count: " << vertexCount << std::endl;

        for(uint32_t i = 0; i < vertexCount; i++){
            ModelVertex vertex;
            for(ShaderMetadata::ShaderInputSlotIdentifier identifier : targetedInputSlots){
                vertex.vertexValues.push_back(OpenGL_Value::readFromStringstream(modelstream, identifier.getSlotType())); // read an OpenGL_Value from the stringstream of the matching type
            }
            vertices.push_back(vertex);
        }

        uint32_t indexCount;
        modelstream >> indexCount;

        // std::cout << "Index count: " << indexCount << std::endl;

        for(uint32_t i = 0; i < indexCount; i++){
            uint32_t index;
            modelstream >> index;
            indices.push_back(index);
        }
    }

    ModelData::~ModelData()
    {
        // no special behavior needed
    }
}