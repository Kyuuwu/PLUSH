#include <vector>

#include "ShaderUniforms.h"

namespace OPENGL_management {
    std::string getVertexShaderPath(std::string filename);
    std::string getFragmentShaderPath(std::string filename);
    std::string getComboShaderPath(std::string filename);

    class Shader{
        public:
            Shader(const char* vertexPath, const char* fragmentPath, const char *name);

            void use();

            void setUniform(ShaderUniformValue &value, ShaderUniformTarget &target);

            void setUniform(ShaderUniform &uniform);

            std::vector<ShaderInput> getInputs();
            std::vector<ShaderUniformSlot> getUniformSlots();

            void addUniformSlots(std::string path);

            unsigned int getID();

            std::string getName();

            void setBeingUsed(bool value);

            void resetAllUniformSetChecks();
            void resetPerLayerUniformSetChecks();
            void resetPerInstanceUniformSetChecks();

            void setUnsetUniformsToDefault();

            void DEBUG_LIST_UNIFORM_SLOTS();

        private:
            void generateInputs(std::string vertexInputPath);

            void setUniform(ShaderUniformValue &value, ShaderUniformSlot &uniform);
            void setUniform(ShaderUniformValue &value, int index);

            ShaderUniformSlot getSlotForTarget(ShaderUniformTarget target);
            int getSlotIndexForTarget(ShaderUniformTarget &target);

            void addSlot(ShaderUniformSlot slot);

            void checkCompileErrors(unsigned int shader, std::string type);

            std::string name;

            unsigned int ShaderID;

            bool beingUsed = false;

            std::vector<ShaderUniformSlot> uniforms;
            std::vector<ShaderInput> inputs;
    };
}