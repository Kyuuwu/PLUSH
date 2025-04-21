#include <cstdint>
#include <iostream>
#include <memory>

#include "Entity/EntitySpec.hpp"
#include "Entity/ManagedEntity.hpp"
#include "EntityMods/DrawMod.hpp"
#include "EntityMods/ResolverMod.hpp"
#include "GlobalEngineState.hpp"
#include "GraphicsLayer/GraphicsLayerSpec.hpp"
#include "GraphicsLayer/ManagedGraphicsLayer.hpp"
#include "OpenGL.h"
#include "PlushEngine.hpp"
#include "PlushGraphics.hpp"
#include "PlushGraphicsException.hpp"
#include "PlushGraphics/include/GlobalGraphicsState.hpp"
#include "OpenGL_Type.hpp"

#include "PlushUtilException.hpp"
#include "Texture2D/ManagedTexture2D.hpp"
#include "UniformResolver.hpp"

void runProgram(){

    std::cout << "Hello, world!\n";
    PlushGraphics::GlobalGraphicsState::initializeOpenGL();

    PlushGraphics::ManagedWindow window = PlushGraphics::GlobalGraphicsState::getWindow(PlushGraphics::GlobalGraphicsState::getActiveWindowIdentifier());
    PlushGraphics::WindowIdentifier id1 = window.getIdentifier();

    PlushGraphics::WindowSettings window2settings;
    window2settings.windowName = "nyanya";
    window2settings.clearColor = glm::vec4(0.7, 0.3, 0.3, 1.0);
    PlushGraphics::WindowSpec spec2(PlushGraphics::UniformResolvers::NoOpResolver(), window2settings);
    PlushGraphics::WindowIdentifier id2 = PlushGraphics::GlobalGraphicsState::windowRegistry.loadItem(spec2);
    PlushGraphics::ManagedWindow win2 = PlushGraphics::GlobalGraphicsState::getWindow(id2);

    // window.switchContextToWindow();

    PlushGraphics::ShaderSpec spec("shader1");

    PlushGraphics::ManagedShader shader = PlushGraphics::GlobalGraphicsState::getShader(PlushGraphics::GlobalGraphicsState::loadShader(spec));
    
    std::cout << "Identifier: " << shader.getIdentifier().getShaderName() << std::endl;
    for(PlushGraphics::ShaderMetadata::ShaderUniformSlotIdentifier uniSlot : shader.getUniformSlotIdentifiers()){
        std::cout << "    Uniform: " << PlushGraphics::getStringFromType(uniSlot.getSlotType()) 
            << " " << uniSlot.getSlotName() << std::endl;
    }

    PlushGraphics::ShaderMetadata::ShaderUniformPayload payload(shader.getUniformSlotIdentifiers()[0], PlushGraphics::OpenGL_Value::create_vec4(glm::vec4(0.5,0.2,0.2,1.0)));

    PlushGraphics::ShaderMetadata::ShaderUniformPayload payload2(shader.getUniformSlotIdentifiers()[0], PlushGraphics::OpenGL_Value::create_vec4(glm::vec4(0.3,0.6,0.2,1.0)));

    for(PlushGraphics::ShaderMetadata::ShaderInputSlotIdentifier inputSlot : shader.getInputSlotIdentifiers()){
        std::cout << "    Input: " << PlushGraphics::getStringFromType(inputSlot.getSlotType()) 
            << " " << inputSlot.getSlotName() << std::endl;
    }

    PlushGraphics::ModelDataSpec mspec("model1.txt");
    PlushGraphics::ManagedModelData modeldata = PlushGraphics::GlobalGraphicsState::modelDataRegistry.getItem(PlushGraphics::GlobalGraphicsState::modelDataRegistry.loadItem(mspec));

    PlushGraphics::ModelInstanceSpec instspec(modeldata, shader);
    PlushGraphics::ManagedModelInstance instst = PlushGraphics::GlobalGraphicsState::getModelInstance(PlushGraphics::GlobalGraphicsState::loadModelInstance(instspec));

    PlushGraphics::Texture2DSpec tspec(PlushGraphics::Texture2DSpec("wall.jpg"));
    PlushGraphics::ManagedTexture2D texture = PlushGraphics::GlobalGraphicsState::getTexture2D(PlushGraphics::GlobalGraphicsState::loadTexture2D(tspec));

    PlushGraphics::GraphicsLayerSpec layerspec((PlushGraphics::UniformResolvers::NoOpResolver()));
    PlushGraphics::ManagedGraphicsLayer layer = PlushGraphics::GlobalGraphicsState::getGraphicsLayer(PlushGraphics::GlobalGraphicsState::loadGraphicsLayer(layerspec));

    PlushGraphics::ManagedGraphicsLayer layer2 = PlushGraphics::GlobalGraphicsState::getGraphicsLayer(PlushGraphics::GlobalGraphicsState::loadGraphicsLayer(layerspec));

    PlushEngine::ManagedEntity ent = PlushEngine::GlobalEngineState::getEntity(PlushEngine::GlobalEngineState::loadEntity(PlushEngine::EntitySpec()))
        .addEntityMod(PlushEngine::EntityMods::DrawMod(instst,layer).withPrimaryTexture(texture))
        .addEntityMod(PlushEngine::EntityMods::ResolverMod(PlushGraphics::UniformResolvers::PreloadedUniformsResolver({payload})));

    PlushEngine::ManagedEntity ent2 = 
        PlushEngine::GlobalEngineState::getEntity(PlushEngine::GlobalEngineState::loadEntity(PlushEngine::EntitySpec()))
        .addEntityMod(PlushEngine::EntityMods::DrawMod(instst,layer2).withPrimaryTexture(texture))
        .addEntityMod(PlushEngine::EntityMods::ResolverMod(PlushGraphics::UniformResolvers::PreloadedUniformsResolver({payload2})));
    

    window.addGraphicsLayer(layer);
    win2.addGraphicsLayer(layer2);

    uint32_t i = 0;

    while(!window.getWindowShouldClose() && !win2.getWindowShouldClose()){
        window.performDrawCycle();
        glfwPollEvents();

        win2.performDrawCycle();
        glfwPollEvents();

        i++;
        if(i % 60 == 0){
            std::cout << "Frame " << i << std::endl;
        }
    }

    PlushGraphics::GlobalGraphicsState::terminateOpenGL();

}

int main(int, char**) {
    try{
        runProgram();
    } catch (PlushUtil::PlushUtilException e){
        PlushUtil::describeException(e);
    } catch (PlushGraphics::PlushGraphicsException e){
        PlushGraphics::describeException(e);
    }

    return 0;
}

