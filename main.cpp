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
        std::cout << "Loaded" << std::endl;
    }

    PlushGraphics::ManagedShader test = shadreg.getItem(id);
    const PlushGraphics::Shader& debugRef = test.DEBUG_getConstReference();
    std::cout << "Identifier: " << debugRef.getIdentifier().getShaderName() << std::endl;
    for(PlushGraphics::ShaderMetadata::ShaderUniformSlotIdentifier uniSlot : debugRef.getUniformSlotIdentifiers()){
        std::cout << "    Uniform: " << PlushGraphics::getStringFromType(uniSlot.getSlotType()) 
            << " " << uniSlot.getSlotName() << std::endl;
    }
    for(PlushGraphics::ShaderMetadata::ShaderInputSlotIdentifier inputSlot : debugRef.getInputSlotIdentifiers()){
        std::cout << "    Input: " << PlushGraphics::getStringFromType(inputSlot.getSlotType()) 
            << " " << inputSlot.getSlotName() << std::endl;
    }

    PlushGraphics::OpenGL::terminateOpenGL();

    return 0;

}
