#include <iostream>

#include "WindowBuilder.hpp"
#include "Window.hpp"
#include "PlushGraphicsOpenGL.hpp"

#include "OpenGL.h"

int main(int, char**) {
    std::cout << "Hello, world!\n";

    PlushGraphics::OpenGL::initializeOpenGL();

    PlushGraphics::WindowBuilder builder;

    PlushGraphics::Window window2(builder);



    while(true){

    }

    // PlushGraphics::OpenGL::terminateOpenGL();

    // std::unique_ptr<PlushGraphics::Shader> susptr = std::make_unique<PlushGraphics::Shader>();
    
    // Tester<PlushGraphics::Shader> a(std::move(susptr));

    // testFunc();

    // PlushUtil::ManagedObject<PlushGraphics::Shader> test(std::move(susptr));

    // PlushGraphics::ManagedShader test(std::move(susptr));


    // PlushGraphics::ManagedShader test2 = test.clone();

    // PlushGraphics::ShaderRegistry reg;

    return 0;

}
