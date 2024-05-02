#include "PLUSH_core_includes.h"

#include "Helpers.h"
#include "VectorNicknames.h"

#include "DiceGame.h"

#include <iostream>

DiceGame::DiceGame(){
    std::shared_ptr<PLUSH::WindowHandler> newwindow(new PLUSH::WindowHandler("DiceGame"));
    window = newwindow;

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

    ground_entity->getInstanceAsSharedPtr("Default")->setLayerOrder(10);

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