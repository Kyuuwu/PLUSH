#include <iostream>

#include "OpenGL.h"
#include "PlushGraphicsOpenGL.hpp"
#include "OpenGL_Type.hpp"

#include "UniformResolver.hpp"

int main(int, char**) {

    std::cout << "Hello, world!\n";
    PlushGraphics::GlobalGraphicsState::initializeOpenGL();

    PlushGraphics::ManagedWindow window = PlushGraphics::GlobalGraphicsState::getWindow(PlushGraphics::GlobalGraphicsState::getActiveWindowIdentifier());
    PlushGraphics::WindowIdentifier id1 = window.getIdentifier();

    PlushGraphics::WindowSpec spec2("nya");
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
    PlushGraphics::UniformResolvers::PreloadedUniformsResolver p({texturePayload});

    PlushGraphics::DrawableRegistry dreg;
    PlushGraphics::DrawableSpec dspec(p, instst);
    PlushGraphics::ManagedDrawable d1 = dreg.getItem(dreg.loadItem(dspec));

    PlushGraphics::DrawableSpec dspec2((PlushGraphics::UniformResolvers::PreloadedUniformsResolver({texturePayload2})), instst);
    PlushGraphics::ManagedDrawable d2 = dreg.getItem(dreg.loadItem(dspec2));


    while(!window.getWindowShouldClose()){
        PlushGraphics::GlobalGraphicsState::switchContextToWindow(id1);
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.useShader();
        shader.clearWindowLevelUniforms();
        shader.prepareForWindowUniforms();
        shader.setUniformNew(payload);

        texture.bindToTextureUnit(1);

        shader.clearLayerLevelUniforms();

        d1.draw();

        window.swapBuffers();
        glfwPollEvents();

        PlushGraphics::GlobalGraphicsState::switchContextToWindow(id2);
        glClearColor(0.7, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.useShader();
        shader.clearWindowLevelUniforms();
        shader.prepareForWindowUniforms();
        shader.setUniformNew(payload2);

        texture.bindToTextureUnit(2);

        shader.clearLayerLevelUniforms();

        d2.draw();

        win2.swapBuffers();
        glfwPollEvents();

        // std::cout << "Frame" << std::endl;
    }

    PlushGraphics::GlobalGraphicsState::terminateOpenGL();

    return 0;

}
