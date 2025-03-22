#include <iostream>

#include "GraphicsLayer/GraphicsLayerSpec.hpp"
#include "GraphicsLayer/ManagedGraphicsLayer.hpp"
#include "OpenGL.h"
#include "PlushGraphics.hpp"
#include "PlushGraphicsException.hpp"
#include "PlushGraphics/include/GlobalGraphicsState.hpp"
#include "OpenGL_Type.hpp"

#include "PlushUtilException.hpp"
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

    window.switchContextToWindow();

    PlushGraphics::ShaderSpec spec("shader1");

    PlushGraphics::ManagedShader shader = PlushGraphics::GlobalGraphicsState::getShader(PlushGraphics::GlobalGraphicsState::loadShader(spec));
    
    std::cout << "Identifier: " << shader.getIdentifier().getShaderName() << std::endl;
    for(PlushGraphics::ShaderMetadata::ShaderUniformSlotIdentifier uniSlot : shader.getUniformSlotIdentifiers()){
        std::cout << "    Uniform: " << PlushGraphics::getStringFromType(uniSlot.getSlotType()) 
            << " " << uniSlot.getSlotName() << std::endl;
    }

    PlushGraphics::ShaderMetadata::ShaderUniformPayload payload(shader.getUniformSlotIdentifiers()[0], PlushGraphics::OpenGL_Value::create_vec4(glm::vec4(0.5,0.2,0.2,1.0)));

    shader.tryToSetUniform(payload);

    PlushGraphics::ShaderMetadata::ShaderUniformPayload payload2(shader.getUniformSlotIdentifiers()[0], PlushGraphics::OpenGL_Value::create_vec4(glm::vec4(0.3,0.6,0.2,1.0)));

    for(PlushGraphics::ShaderMetadata::ShaderInputSlotIdentifier inputSlot : shader.getInputSlotIdentifiers()){
        std::cout << "    Input: " << PlushGraphics::getStringFromType(inputSlot.getSlotType()) 
            << " " << inputSlot.getSlotName() << std::endl;
    }

    PlushGraphics::ModelDataSpec mspec("model1.txt");
    
    PlushGraphics::ManagedModelData modeldata = PlushGraphics::GlobalGraphicsState::modelDataRegistry.getItem(PlushGraphics::GlobalGraphicsState::modelDataRegistry.loadItem(mspec));

    // PlushGraphics::GlobalGraphicsState::switchContextToWindow(id1);
    PlushGraphics::ModelInstanceSpec instspec(modeldata, shader);
    PlushGraphics::ManagedModelInstance instst = PlushGraphics::GlobalGraphicsState::getModelInstance(PlushGraphics::GlobalGraphicsState::loadModelInstance(instspec));

    // PlushGraphics::GlobalGraphicsState::switchContextToWindow(id2);
    PlushGraphics::Texture2DSpec tspec(PlushGraphics::Texture2DSpec("wall.jpg"));
    PlushGraphics::ManagedTexture2D texture = PlushGraphics::GlobalGraphicsState::getTexture2D(PlushGraphics::GlobalGraphicsState::loadTexture2D(tspec));

    PlushGraphics::ShaderMetadata::ShaderUniformPayload texturePayload(shader.getUniformSlotIdentifiers()[1], PlushGraphics::OpenGL_Value::create_sampler_2D(1));
    PlushGraphics::ShaderMetadata::ShaderUniformPayload texturePayload2(shader.getUniformSlotIdentifiers()[1], PlushGraphics::OpenGL_Value::create_sampler_2D(2));


    // PlushGraphics::UniformResolvers::NoOpResolver t;
    PlushGraphics::UniformResolvers::PreloadedUniformsResolver p({texturePayload, payload});

    PlushGraphics::DrawableSpec dspec(p, instst);
    PlushGraphics::ManagedDrawable d1 = PlushGraphics::GlobalGraphicsState::getDrawable(PlushGraphics::GlobalGraphicsState::loadDrawable(dspec));

    PlushGraphics::DrawableSpec dspec2((PlushGraphics::UniformResolvers::PreloadedUniformsResolver({texturePayload2, payload2})), instst);
    PlushGraphics::ManagedDrawable d2 = PlushGraphics::GlobalGraphicsState::getDrawable(PlushGraphics::GlobalGraphicsState::loadDrawable(dspec2));

    PlushGraphics::GraphicsLayerSpec layerspec((PlushGraphics::UniformResolvers::NoOpResolver()));
    PlushGraphics::ManagedGraphicsLayer layer = PlushGraphics::GlobalGraphicsState::getGraphicsLayer(PlushGraphics::GlobalGraphicsState::loadGraphicsLayer(layerspec));

    PlushGraphics::ManagedGraphicsLayer layer2 = PlushGraphics::GlobalGraphicsState::getGraphicsLayer(PlushGraphics::GlobalGraphicsState::loadGraphicsLayer(layerspec));

    layer.addDrawable(d1);
    layer2.addDrawable(d2);

    window.addGraphicsLayer(layer);
    win2.addGraphicsLayer(layer2);

    while(!window.getWindowShouldClose()){
        PlushGraphics::GlobalGraphicsState::switchContextToWindow(id1); // needed for tampering with textures in main function
        
        texture.bindToTextureUnit(1);

        window.performDrawCycle();
        glfwPollEvents();

        PlushGraphics::GlobalGraphicsState::switchContextToWindow(id2); // needed for tampering with textures in main function

        texture.bindToTextureUnit(2);

        win2.performDrawCycle();
        glfwPollEvents();
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

