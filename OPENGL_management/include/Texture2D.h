#include <string>

namespace OPENGL_management {
    std::string getTexture2DPath(std::string filename);
    std::string getTexture2DComboPath(std::string filename);

    class Texture2D{
        public:
            Texture2D(std::string name, const char* texturePath, int width, int height, bool useAlpha);
            Texture2D(const char* comboFile);

            void use(unsigned int textureUnit = 0);
        
            unsigned int getID();

            std::string getName();

        private:
            void initializeTexture(std::string name, const char* texturePath, int width, int height, bool useAlpha);

            std::string name;

            unsigned int textureID;
            // unsigned int currentTextureUnit = 0;

            int texture_width;
            int texture_height;
            int texture_num_channels;
    };
}