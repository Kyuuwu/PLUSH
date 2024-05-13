#include "OPENGL_management_includes.h"
#include "Helpers.h"
#include <iostream>

namespace OPENGL_management {
    bool TextureLibrary::isTextureLibraryInitialized(){
        return isInitialized;
    }
    
    uint32_t TextureLibrary::getNextEntityReservedTextureUnit()
    {
        uint32_t return_value = nextEntityReservedTextureUnit;

        nextEntityReservedTextureUnit++;

        if (nextEntityReservedTextureUnit >= numEntityReservedTextureUnits){
            nextEntityReservedTextureUnit = 0;
        }

        return return_value;
    }
    
    uint32_t TextureLibrary::getNextLayerReservedTextureUnit()
    {
        uint32_t return_value = nextLayerReservedTextureUnit;

        nextLayerReservedTextureUnit++;

        if (nextLayerReservedTextureUnit >= numTextureUnits){
            nextLayerReservedTextureUnit = numEntityReservedTextureUnits;
        }

        return return_value;
    }

    void TextureLibrary::reInitializeTextureLibrary(){

        initializeTextures_2D_fromList();

        isInitialized = true;
    }

    void TextureLibrary::initializeTextures_2D_fromList(std::string textures2Dlistfile){
        std::stringstream liststream = PLUSH_helpers::getStreamFromFile(getTexture2DPath(textures2Dlistfile));

        std::vector<std::shared_ptr<Texture2D>> newTextureList;

        std::string textureComboFile;

        liststream >> textureComboFile;

        while(liststream){
            newTextureList.push_back(generateTexture2D(textureComboFile+".combo"));
            liststream >> textureComboFile;
        }

        texture2DList = newTextureList;
        listsize = texture2DList.size();
    }

    std::shared_ptr<Texture2D> TextureLibrary::generateTexture2D(std::string comboFile){
        std::shared_ptr<Texture2D> texture(new Texture2D(comboFile.c_str()));
        return texture;
    }

    void TextureLibrary::initializeTextureLibraryIfNeeded(){
        if (!isInitialized){
            reInitializeTextureLibrary();
        }
    }

    std::shared_ptr<Texture2D> TextureLibrary::getTexture2DByName(std::string name){
        initializeTextureLibraryIfNeeded();

        for (unsigned int i = 0; i < listsize; i++){
            if(texture2DList[i]->getName() == name){
                return texture2DList[i];
            }
        }

        throw(TEXTURE2D_NOT_FOUND);
    }
}