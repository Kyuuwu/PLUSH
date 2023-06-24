#include <vector>
#include <memory>
#include <string>

namespace OPENGL_management {
    class Model;

    class ModelLibrary{
        public:
            static std::shared_ptr<Model> getModelByName(std::string name);
            static void reInitializeModelLibrary();
            static bool isModelLibraryInitialized();

        private:
            static void initializeModelLibraryIfNeeded();
            inline static std::vector<std::shared_ptr<Model>> modelList;
            inline static bool isInitialized = false;

    };
}