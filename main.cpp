#include <iostream>

#include "OpenGL_Type.hpp"
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
    PlushGraphics::OpenGL::initializeOpenGL();

    PlushGraphics::ManagedWindow window = PlushGraphics::OpenGL::windowRegistry.getItem(PlushGraphics::OpenGL::getActiveWindowIdentifier());
    PlushGraphics::WindowIdentifier id1 = window.getIdentifier();

    PlushGraphics::WindowSpec spec2("nya");
    PlushGraphics::WindowIdentifier id2 = PlushGraphics::OpenGL::windowRegistry.loadItem(spec2);
    PlushGraphics::ManagedWindow win2 = PlushGraphics::OpenGL::windowRegistry.getItem(id2);

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

    PlushGraphics::ModelDataRegistry modreg;
    PlushGraphics::ModelDataSpec mspec("model1.txt");
    PlushGraphics::ModelDataIdentifier mid("ModelABC");
    modreg.loadItem(mspec);
    if(modreg.isItemLoaded(mid)){
        std::cout << "ModelData is loaded" << std::endl;
    }
    PlushGraphics::ManagedModelData modeldata = modreg.getItem(mid);

    PlushGraphics::ModelInstanceRegistry modinstreg;
    PlushGraphics::ModelInstanceSpec instspec(modeldata, shader);
    modinstreg.loadItem(instspec);
    PlushGraphics::ModelInstanceIdentifier instid(mid, id);
    PlushGraphics::ManagedModelInstance instst = modinstreg.getItem(instid);

    while(!window.getWindowShouldClose()){
        PlushGraphics::OpenGL::switchContextToWindow(id1);
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.useShader();
        shader.setUniform(payload);
        instst.drawModel();

        window.swapBuffers();
        glfwPollEvents();

        PlushGraphics::OpenGL::switchContextToWindow(id2);
        glClearColor(0.7, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.useShader();
        shader.setUniform(payload2);
        instst.drawModel();

        win2.swapBuffers();
        glfwPollEvents();
    }

    PlushGraphics::OpenGL::terminateOpenGL();

    return 0;

}
