#include <vector>

#include "ShaderUniforms.h"

namespace OPENGL_management {
    class Model;
    
    union VertexValue{
        int i;
        unsigned int u;
        float f;
    };

    struct VertexHolder{
        std::vector<VertexValue> vertices;
        std::vector<ShaderInput> inputs;
    };

    std::string getModelPath_Basic(std::string modelname);
    std::string getModelPath_Basic_EBO(std::string modelname);

    class ModelGeneration{
        public:
            static Model* createModel(std::string name, VertexHolder holder);
            static Model* createModel(std::string name, VertexHolder holder, std::vector<unsigned int> indices);

            static VertexHolder loadModelFromFile_Basic(std::string path);
            static std::vector<unsigned int> loadIndicesFromFile_Basic(std::string path);

            static Model* createModelFromFile_Basic(std::string path);
            static Model* createModelFromFile_Basic_EBO(std::string path);

            static unsigned int getVertexValueCount(std::vector<ShaderInput> inputs);
            static unsigned int getInputValueCount(ShaderInput input);
    };
}