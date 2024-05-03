#include <vector>
#include <memory>
#include <string>

namespace OPENGL_management {
    class Shader;

    class ShaderLibrary{
        public:
            static std::shared_ptr<Shader> getShaderByName(std::string name);
            static void reInitializeShaderLibrary();
            static bool isShaderLibraryInitialized();

        private:
            static void initializeShaderLibraryIfNeeded();

            static void addShader(std::string combopath);

            inline static std::vector<std::shared_ptr<Shader>> shaderList;
            inline static bool isInitialized = false;

    };
}