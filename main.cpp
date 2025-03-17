#include <iostream>

#include "Texture2D/ManagedTexture2D.hpp"
#include "OpenGL_Type.hpp"
#include "PlushGraphics.hpp"
#include "Texture2D/Texture2DSpec.hpp"
#include "Texture2D/Texture2D.hpp"
#include "Window/WindowSpec.hpp"
#include "Window/Window.hpp"
#include "Window/WindowRegistry.hpp"
#include "PlushGraphicsOpenGL.hpp"

#include "OpenGL.h"
#include "Shader/ShaderSpec.hpp"
#include "Shader/ShaderRegistry.hpp"
#include "Shader/ShaderUniformSlot.hpp"
#include "Shader/ShaderUniformSlotIdentifier.hpp"
#include "Shader/ShaderUniformPayload.hpp"
#include "Shader/ShaderInputSlot.hpp"
#include "Shader/Shader.hpp"
#include "ModelData/ModelData.hpp"
#include "ModelData/ModelDataSpec.hpp"
#include "ModelData/ModelDataRegistry.hpp"

#include "ModelInstance/ModelInstance.hpp"
#include "ModelInstance/ModelInstanceSpec.hpp"
#include "ModelInstance/ModelInstanceIdentifier.hpp"
#include "ModelInstance/ModelInstanceRegistry.hpp"

#include "Drawable/Drawable.hpp"
#include "UniformResolver.hpp"
#include "Drawable/DrawableRegistry.hpp"
#include "Drawable/DrawableSpec.hpp"
#include "Drawable/ManagedDrawable.hpp"

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
        shader.tryToSetUniform(payload);

        texture.bindToTextureUnit(1);
        d1.draw();

        window.swapBuffers();
        glfwPollEvents();

        PlushGraphics::GlobalGraphicsState::switchContextToWindow(id2);
        glClearColor(0.7, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.useShader();
        shader.tryToSetUniform(payload2);

        texture.bindToTextureUnit(2);
        d2.draw();

        win2.swapBuffers();
        glfwPollEvents();
    }

    PlushGraphics::GlobalGraphicsState::terminateOpenGL();

    return 0;

}
