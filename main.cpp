#include <iostream>

#include "OpenGL_Type.hpp"
#include "WindowBuilder.hpp"
#include "Window.hpp"
#include "PlushGraphicsOpenGL.hpp"

#include "OpenGL.h"
#include "ShaderSpec.hpp"
#include "ShaderRegistry.hpp"
#include "ShaderUniformSlot.hpp"
#include "ShaderUniformSlotIdentifier.hpp"
#include "ShaderInputSlot.hpp"
#include "Shader.hpp"
#include "ModelData.hpp"
#include "ModelDataSpec.hpp"
#include "ModelDataRegistry.hpp"

#include "ModelInstance.hpp"
#include "ModelInstanceSpec.hpp"
#include "ModelInstanceIdentifier.hpp"

int main(int, char**) {
    std::cout << "Hello, world!\n";
    PlushGraphics::OpenGL::initializeOpenGL();

    PlushGraphics::WindowBuilder builder;
    PlushGraphics::Window window2(builder);

    PlushGraphics::ShaderRegistry shadreg;
    PlushGraphics::ShaderSpec spec("shader1");
    PlushGraphics::ShaderIdentifier id("shader1");
    shadreg.loadItem(spec);

    if(shadreg.isItemLoaded(id)){
        std::cout << "Shader is loaded" << std::endl;
    }

    PlushGraphics::ManagedShader shader = shadreg.getItem(id);
    const PlushGraphics::Shader& debugRef = shader.DEBUG_getConstReference();
    std::cout << "Identifier: " << debugRef.getIdentifier().getShaderName() << std::endl;
    for(PlushGraphics::ShaderMetadata::ShaderUniformSlotIdentifier uniSlot : debugRef.getUniformSlotIdentifiers()){
        std::cout << "    Uniform: " << PlushGraphics::getStringFromType(uniSlot.getSlotType()) 
            << " " << uniSlot.getSlotName() << std::endl;
    }
    for(PlushGraphics::ShaderMetadata::ShaderInputSlotIdentifier inputSlot : debugRef.getInputSlotIdentifiers()){
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

    PlushGraphics::ModelInstanceSpec instspec(modeldata, shader);
    PlushGraphics::ModelInstance inst(instspec);

    while(!glfwWindowShouldClose(window2.windowPointer)){
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.useShader();
        inst.draw();

        glfwSwapBuffers(window2.windowPointer);
        glfwPollEvents();
    }

    PlushGraphics::OpenGL::terminateOpenGL();

    return 0;

}
