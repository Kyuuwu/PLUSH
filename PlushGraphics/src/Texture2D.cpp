#include "../include/Texture2D/Texture2D.hpp"
#include "../include/Texture2D/Texture2DSpec.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glad/glad.h"
#include <iostream>
#include "PlushUtilException.hpp"

namespace PlushGraphics {
    Texture2D::Texture2D(Texture2DSpec spec)
    : identifier(spec.getTexture2DFileName())
    {
        glGenTextures(1,&textureRefID);

        glBindTexture(GL_TEXTURE_2D, textureRefID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;

        std::string filePath = "textures/"+spec.getTexture2DFileName();

        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(filePath.c_str(), &width,&height, &nrChannels, 0);
        if(data){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else{
            std::cout << "Failed to load texture from path " << filePath << std::endl;
            throw(PlushUtil::PlushUtilException::FILE_READ_ERROR);
        }
        stbi_image_free(data);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &textureRefID);
    }

    void Texture2D::_bindToTextureUnit(u_int32_t textureUnit) {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, textureRefID);
    }
}