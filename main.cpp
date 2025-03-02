#include <iostream>

#include "OpenGL_Type.hpp"
#include "Texture2DSpec.hpp"
#include "Texture2D.hpp"
#include "WindowSpec.hpp"
#include "Window.hpp"
#include "WindowRegistry.hpp"
#include "PlushGraphicsOpenGL.hpp"

#include "OpenGL.h"
#include "ShaderSpec.hpp"
#include "ShaderRegistry.hpp"
#include "ShaderUniformSlot.hpp"
#include "ShaderUniformSlotIdentifier.hpp"
#include "ShaderUniformPayload.hpp"
#include "ShaderInputSlot.hpp"
#include "Shader.hpp"
#include "ModelData.hpp"
#include "ModelDataSpec.hpp"
#include "ModelDataRegistry.hpp"

#include "ModelInstance.hpp"
#include "ModelInstanceSpec.hpp"
#include "ModelInstanceIdentifier.hpp"
#include "ModelInstanceRegistry.hpp"

int main(int, char**) {
    std::cout << "Hello, world!\n";
    PlushGraphics::GlobalGraphicsState::initializeOpenGL();

    PlushGraphics::ManagedWindow window = PlushGraphics::GlobalGraphicsState::windowRegistry.getItem(PlushGraphics::GlobalGraphicsState::getActiveWindowIdentifier());
    PlushGraphics::WindowIdentifier id1 = window.getIdentifier();

    PlushGraphics::WindowSpec spec2("nya");
    PlushGraphics::WindowIdentifier id2 = PlushGraphics::GlobalGraphicsState::windowRegistry.loadItem(spec2);
    PlushGraphics::ManagedWindow win2 = PlushGraphics::GlobalGraphicsState::windowRegistry.getItem(id2);

    window.switchContextToWindow();

    PlushGraphics::ShaderRegistry shadreg;
    PlushGraphics::ShaderSpec spec("shader1");
    PlushGraphics::ShaderIdentifier id("shader1");
    shadreg.loadItem(spec);

    if(shadreg.isItemLoaded(id)){
        std::cout << "Shader is loaded" << std::endl;
    }

    PlushGraphics::ManagedShader shader = shadreg.getItem(id);
    std::cout << "Identifier: " << shader.getIdentifier().getShaderName() << std::endl;
    for(PlushGraphics::ShaderMetadata::ShaderUniformSlotIdentifier uniSlot : shader.getUniformSlotIdentifiers()){
        std::cout << "    Uniform: " << PlushGraphics::getStringFromType(uniSlot.getSlotType()) 
            << " " << uniSlot.getSlotName() << std::endl;
    }

    PlushGraphics::ShaderMetadata::ShaderUniformPayload payload(shader.getUniformSlotIdentifiers()[0], PlushGraphics::OpenGL_Value::create_vec4(glm::vec4(0.5,0.2,0.2,1.0)));

    shader.setUniform(payload);

    PlushGraphics::ShaderMetadata::ShaderUniformPayload payload2(shader.getUniformSlotIdentifiers()[0], PlushGraphics::OpenGL_Value::create_vec4(glm::vec4(0.3,0.6,0.2,1.0)));

    for(PlushGraphics::ShaderMetadata::ShaderInputSlotIdentifier inputSlot : shader.getInputSlotIdentifiers()){
        std::cout << "    Input: " << PlushGraphics::getStringFromType(inputSlot.getSlotType()) 
            << " " << inputSlot.getSlotName() << std::endl;
    }

    PlushGraphics::ModelDataSpec mspec("model1.txt");
    PlushGraphics::ModelDataIdentifier mid("ModelABC");
    PlushGraphics::GlobalGraphicsState::modelDataRegistry.loadItem(mspec);
    if(PlushGraphics::GlobalGraphicsState::modelDataRegistry.isItemLoaded(mid)){
        std::cout << "ModelData is loaded" << std::endl;
    }
    PlushGraphics::ManagedModelData modeldata = PlushGraphics::GlobalGraphicsState::modelDataRegistry.getItem(mid);

    // PlushGraphics::GlobalGraphicsState::switchContextToWindow(id1);
    PlushGraphics::ModelInstanceSpec instspec(modeldata, shader);
    PlushGraphics::GlobalGraphicsState::modelInstanceRegistry.loadItem(instspec);
    PlushGraphics::ModelInstanceIdentifier instid(mid, id);
    PlushGraphics::ManagedModelInstance instst = PlushGraphics::GlobalGraphicsState::modelInstanceRegistry.getItem(instid);

    // PlushGraphics::GlobalGraphicsState::switchContextToWindow(id2);
    PlushGraphics::Texture2D texture(PlushGraphics::Texture2DSpec("wall.jpg"));

    PlushGraphics::ShaderMetadata::ShaderUniformPayload texturePayload(shader.getUniformSlotIdentifiers()[1], PlushGraphics::OpenGL_Value::create_sampler_2D(1));

    while(!window.getWindowShouldClose()){
        PlushGraphics::GlobalGraphicsState::switchContextToWindow(id1);
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.useShader();
        shader.setUniform(payload);

        texture.bindToTextureUnit(1);
        shader.setUniform(texturePayload);
        instst.drawModel();

        window.swapBuffers();
        glfwPollEvents();

        PlushGraphics::GlobalGraphicsState::switchContextToWindow(id2);
        glClearColor(0.7, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.useShader();
        shader.setUniform(payload2);

        texture.bindToTextureUnit(1);
        shader.setUniform(texturePayload);
        instst.drawModel();

        win2.swapBuffers();
        glfwPollEvents();
    }

    PlushGraphics::GlobalGraphicsState::terminateOpenGL();

    return 0;

}
