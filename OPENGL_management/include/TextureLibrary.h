#include <vector>
#include <memory>
#include <string>

namespace OPENGL_management {
    class Texture2D;

    class TextureLibrary{
        public:
            static std::shared_ptr<Texture2D> getTexture2DByName(std::string name);
            static void reInitializeTextureLibrary();
            static bool isTextureLibraryInitialized();

        private:
            static void initializeTextureLibraryIfNeeded();
            static std::shared_ptr<Texture2D> generateTexture2D(std::string comboFile);

            static void initializeTextures_2D_fromList(std::string textures2Dlistfile = "textures_2D_list.txt");

            inline static std::vector<std::shared_ptr<Texture2D>> texture2DList;
            inline static bool isInitialized = false;
            inline static unsigned int listsize = 0;

    };
}