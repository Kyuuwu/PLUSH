#include "PLUSH_core_includes.h"

#include "Helpers.h"
#include "VectorNicknames.h"

#include "DiceGame.h"

#include <iostream>

DiceGame::DiceGame(){
    std::shared_ptr<PLUSH::WindowHandler> newwindow(new PLUSH::WindowHandler("DiceGame"));
    window = newwindow;

    // std::shared_ptr<PLUSH::Entity_2D_Layer> layer(new PLUSH::Entity_2D_Layer("LayerBackground"));
    // layer->setLayerHalfDimensions(1.0f, 1.0f);
    // layer->setLayerPositionCOM(0.0f, 0.0f);

    // std::shared_ptr<PLUSH::Entity_2D_Animated_Layer> layer2(new PLUSH::Entity_2D_Animated_Layer("LayerEntities"));
    // layer2->setLayerHalfDimensions(1.0f, 1.0f);
    // layer2->setLayerPositionCOM(0.0f, 0.0f);

    // std::shared_ptr<PLUSH::Entity_2D_Animated_Layer> layer3(new PLUSH::Entity_2D_Animated_Layer("LayerForeground"));
    // layer3->setLayerHalfDimensions(1.0f, 1.0f);
    // layer3->setLayerPositionCOM(0.0f, 0.0f);

    // window->addDrawableLayer(layer);
    // window->addDrawableLayer(layer2);
    // window->addDrawableLayer(layer3);

    // std::shared_ptr<PLUSH::Entity_2D_Collection> collection1(new PLUSH::Entity_2D_Collection);
    // std::shared_ptr<PLUSH::Entity_2D_Collection> collection2(new PLUSH::Entity_2D_Collection);
    // std::shared_ptr<PLUSH::Entity_2D_Collection> collection3(new PLUSH::Entity_2D_Collection);

    // layer->setEntityCollection(collection1);
    // layer2->setEntityCollection(collection2);
    // layer3->setEntityCollection(collection3);

    // collection1->addEntity(PLUSH::generateBasicTexturedSquareEntity(
    //     "Backdrop", "BlackRectangle", 
    //     vZero(), vScreenfiller()));

    // collection1->addEntity(PLUSH::generateBasicTexturedSquareEntity(
    //     "Ground", "OrangeSquare", 
    //     -1.2f*vY(), vScreenfiller()));

    window->addStandardLayer(
        std::shared_ptr<PLUSH::Standard_Layer>(
            new PLUSH::Standard_Layer(
                "LayerBackground", 
                glm::vec2(0.0f, 0.0f), 
                glm::vec2(1.0f, 1.0f))));
    window->addStandardLayer(
        std::shared_ptr<PLUSH::Standard_Layer>(
            new PLUSH::Standard_Layer(
                "LayerEntities", 
                glm::vec2(0.0f, 0.0f), 
                glm::vec2(1.0f, 1.0f))));
    window->addStandardLayer(
        std::shared_ptr<PLUSH::Standard_Layer>(
            new PLUSH::Standard_Layer(
                "LayerForeground", 
                glm::vec2(0.0f, 0.0f), 
                glm::vec2(1.0f, 1.0f))));

    std::shared_ptr<PLUSH::Entity> backdrop_entity = PLUSH::generateBasicTexturedSquareEntity(
        "Backdrop", "BlackRectangle", 
        vZero(), vScreenfiller());

    std::shared_ptr<PLUSH::Entity> ground_entity = PLUSH::generateBasicTexturedSquareEntity(
        "Ground", "OrangeSquare", 
        -1.2f*vY(), vScreenfiller());

    backdrop_entity->addInstanceToLayer("Default", window->getStandardLayer("LayerBackground").lock());
    ground_entity->addInstanceToLayer("Default", window->getStandardLayer("LayerBackground").lock());

    entities.push_back(backdrop_entity);
    entities.push_back(ground_entity);
}

void DiceGame::run(){
    float currentTime = PLUSH_helpers::GetTime();

    float time_float_prev = currentTime;

    while(!window->ShouldClose()){

        window->draw(); // draw

        //check and process (TBD) inputs
        PLUSH_helpers::PollEvents_GLFW();

        time_float_prev = currentTime;
        currentTime = PLUSH_helpers::GetTime();
    }
    PLUSH_helpers::Terminate_GLFW();
}