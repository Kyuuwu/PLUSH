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

            int getGridWidth();
            int getGridHeight();

            void setIsGrid(bool isgrid);
            bool getIsGrid();
            void setGridDimensions(int w, int h);

        private:
            void initializeTexture(std::string name, const char* texturePath, int width, int height, bool useAlpha);

            std::string name;

            unsigned int textureID;
            // unsigned int currentTextureUnit = 0;

            unsigned int texture_width;
            unsigned int texture_height;
            unsigned int texture_num_channels;

            bool isGrid = false;
            unsigned int texture_grid_width = 0;
            unsigned int texture_grid_height = 0;
    };
}