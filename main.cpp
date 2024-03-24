#include <iostream>

#include "PLUSH_core_includes.h"
#include "Helpers.h"
#include "ShaderLibrary.h"

int main(int, char**) {
    std::cout << "Hello, world!\n";

    std::shared_ptr<PLUSH::WindowHandler> window(new PLUSH::WindowHandler("2DGame"));

    std::shared_ptr<PLUSH::Entity_2D_Animated_Layer> layer(new PLUSH::Entity_2D_Animated_Layer("Layer_2D"));

    std::shared_ptr<PLUSH::Entity_2D_Collection> collection(new PLUSH::Entity_2D_Collection);

    std::shared_ptr<PLUSH::Entity> entity(new PLUSH::Entity("Random", "square2D.vx"));
    entity->getStatusPointer()->visible = true;
    entity->setTexture2DUniform("primaryTexture", "DragonTile");

    entity->setScale(glm::vec3(1.0f, 0.3f, 1.0f));
    entity->setPosition(glm::vec3(0.5f, 0.2f, 0.0f));

    entity->getStatusPointer()->animated = true;
    entity->getStatusPointer()->animation_index = 0;
    entity->getStatusPointer()->animation_loop_end = 3;
    entity->getStatusPointer()->animation_loop_start = 0;

    window->addDrawableLayer(layer);

    collection->addEntity(entity);

    layer->setEntityCollection(collection);

    layer->setLayerPositionCOM(0, 0);
    layer->setLayerHalfDimensions(0.9, 0.6);
    layer->setLayerInternalShift(-0.7, 0);


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

    return 0;

}
