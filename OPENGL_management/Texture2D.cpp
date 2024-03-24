#define STB_IMAGE_IMPLEMENTATION
#include "OPENGL_includes.h"
#include "OPENGL_management_includes.h"
#include "Helpers.h"
#include "Exceptions.h"
#include <filesystem>
#include <iostream>

namespace OPENGL_management {
    std::string getTexture2DPath(std::string filename){
        return std::filesystem::current_path().string()+"/textures/2D/"+filename;
    }
    std::string getTexture2DComboPath(std::string filename){
        return std::filesystem::current_path().string()+"/textures/2D/combo/"+filename;
    }

    Texture2D::Texture2D(const char* comboPath){
        std::stringstream combostream = PLUSH_helpers::getStreamFromFile(getTexture2DComboPath(comboPath));

        std::string name;
        std::string path;
        unsigned int width, height;
        bool useAlpha;
        bool is_grid;
        int grid_w;
        int grid_h;

        combostream >> name;
        combostream >> path;
        combostream >> width;
        combostream >> height;
        combostream >> std::boolalpha >> useAlpha;

        if(!combostream){
            std::cout << "Error: texture combo file incomplete" << std::endl;
            throw(PLUSH_helpers::FILE_INCOMPLETE);
        } // for now check this way before because pain editing combo files

        combostream >> std::boolalpha >> is_grid;

        if(!combostream){
            std::cout << "Warning: texture combo file omits grid specs, default to non-grid texture" << std::endl;
            is_grid = false;
            // throw(PLUSH_helpers::FILE_INCOMPLETE);
        }

        if(is_grid){
            combostream >> grid_w;
            combostream >> grid_h;
            setIsGrid(true);
            setGridDimensions(grid_w, grid_h);
        }

        // std::cout << name << std::endl << isGrid << std::endl << texture_grid_width << " " << texture_grid_height << std::endl << std::endl;

        initializeTexture(name, path.c_str(), width, height, useAlpha);
    }

    Texture2D::Texture2D(std::string name, const char* texturePath, int width, int height, bool useAlpha){
        initializeTexture(name, texturePath, width, height, useAlpha);
    }

    void Texture2D::initializeTexture(std::string name, const char *texturePath, int width, int height, bool useAlpha){
        this->name = name;

        stbi_set_flip_vertically_on_load(true);

        std::string fullTexturePath = getTexture2DPath(texturePath);

        unsigned int ID;
        glGenTextures(1, &ID);

        textureID = ID;

        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        texture_width = width;
        texture_height = height;
        texture_num_channels = (useAlpha ? 4: 3);

        int texnumch = texture_num_channels;

        unsigned char* data = stbi_load(fullTexturePath.c_str(), &width, &height, &texnumch, 0);

        if (data)
        {
            GLenum channel_type = (useAlpha ? GL_RGBA : GL_RGB);
            glTexImage2D(GL_TEXTURE_2D, 0, channel_type, width, height, 0, channel_type, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    void Texture2D::use(unsigned int textureUnit){
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    unsigned int Texture2D::getID(){
        return textureID;
    }

    std::string Texture2D::getName(){
        return name;
    }

    int Texture2D::getGridHeight(){
        return texture_grid_height;
    }

    int Texture2D::getGridWidth(){
        return texture_grid_width;
    }

    void Texture2D::setIsGrid(bool isgrid){
        isGrid = isgrid;
    }

    bool Texture2D::getIsGrid(){
        return isGrid;
    }

    void Texture2D::setGridDimensions(int w, int h){
        texture_grid_width = w;
        texture_grid_height = h;
    }

}