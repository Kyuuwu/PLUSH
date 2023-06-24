#include "OPENGL_management_includes.h"

#include <iostream>

namespace OPENGL_management {
    bool ModelLibrary::isModelLibraryInitialized(){
        return isInitialized;
    }

    void ModelLibrary::reInitializeModelLibrary(){
        std::vector<std::shared_ptr<Model>> newModelList;

        std::shared_ptr<Model> tringle(OPENGL_management::ModelGeneration::createModelFromFile_Basic_EBO("tringle.vx"));

        std::shared_ptr<Model> square(OPENGL_management::ModelGeneration::createModelFromFile_Basic_EBO("square.vx"));

        std::shared_ptr<Model> tile(OPENGL_management::ModelGeneration::createModelFromFile_Basic_EBO("tile.vx"));

        tile->addTexture2D("primaryTexture", "AwesomeFace");
        tringle->addTexture2D("primaryTexture", "AwesomeFace");
        square->addTexture2D("primaryTexture", "AwesomeFace");

        newModelList.push_back(tringle);
        newModelList.push_back(square);
        newModelList.push_back(tile);

        modelList = newModelList;
        isInitialized = true;
    }

    void ModelLibrary::initializeModelLibraryIfNeeded(){
        if (!isInitialized){
            reInitializeModelLibrary();
        }
    }

    std::shared_ptr<Model> ModelLibrary::getModelByName(std::string name){
        initializeModelLibraryIfNeeded();

        for (std::shared_ptr<Model> model : modelList){
            if(model->getName() == name){
                return model;
            }
        }

        std::cout << "Model not found." << std::endl;

        throw(MODEL_NOT_FOUND);
    }
}