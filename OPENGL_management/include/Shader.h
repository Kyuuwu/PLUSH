#include <vector>

#include "ShaderUniforms.h"

namespace OPENGL_management {
    std::string getVertexShaderPath(std::string filename);
    std::string getFragmentShaderPath(std::string filename);
    std::string getComboShaderPath(std::string filename);

    class Shader{
        public:
            Shader(std::string comboPath);

            // Shader(const char* vertexPath, const char* fragmentPath, const char *name);

            void use();

            void setUniform(ShaderUniformValue &value, ShaderUniformTarget &target);

            void setUniform(ShaderUniform &uniform);

            void setTexture2DUniform(TextureNamePair namepair, uint32_t textureunit);

            std::vector<ShaderInput> getInputs();
            std::vector<ShaderUniformSlot> getUniformSlots();
            std::vector<ShaderUniformTarget> getUniformTargets();

            unsigned int getID();

            std::string getName();

            void DEBUG_LIST_UNIFORM_SLOTS();



            // void addUniformSlots(std::string path);

            // void setBeingUsed(bool value);

            // void resetAllUniformSetChecks();
            // void resetPerLayerUniformSetChecks();
            // void resetPerInstanceUniformSetChecks();

            // void setUnsetUniformsToDefault();

        private:
            void checkCompileErrors(unsigned int shader, std::string type);

            void addSlot(ShaderUniformSlot slot);

            void setUniform(ShaderUniformValue &value, int index);

            std::vector<ShaderUniformSlot> uniform_slots;
            std::vector<ShaderUniformTarget> uniform_targets;
            std::vector<ShaderInput> inputs;

            std::string name;

            unsigned int ShaderID;

            ShaderUniformSlot getSlotForTarget(ShaderUniformTarget target);
            int getSlotIndexForTarget(ShaderUniformTarget &target);

            void generateTargetList();


            // void setUniform(ShaderUniformValue &value, ShaderUniformSlot &uniform);

            // void generateInputs(std::string vertexInputPath);

            // bool beingUsed = false;
    };
}