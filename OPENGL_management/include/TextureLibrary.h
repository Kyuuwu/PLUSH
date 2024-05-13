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

            static uint32_t getNextEntityReservedTextureUnit();
            static uint32_t getNextLayerReservedTextureUnit();

        private:
            inline static uint32_t nextEntityReservedTextureUnit = 0;

            static const uint32_t numEntityReservedTextureUnits = 4;

            inline static uint32_t nextLayerReservedTextureUnit = numEntityReservedTextureUnits;

            static const uint32_t numTextureUnits = 16;

            static void initializeTextureLibraryIfNeeded();
            static std::shared_ptr<Texture2D> generateTexture2D(std::string comboFile);

            static void initializeTextures_2D_fromList(std::string textures2Dlistfile = "textures_2D_list.txt");

            inline static std::vector<std::shared_ptr<Texture2D>> texture2DList;
            inline static bool isInitialized = false;
            inline static unsigned int listsize = 0;

    };
}