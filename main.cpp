#include <iostream>

#include "ManagedObject.hpp"
#include "ManagedShader.hpp"
#include "Shader.hpp"
// #include "ShaderRegistry.hpp"

int main(int, char**) {
    std::cout << "Hello, world!\n";
    std::unique_ptr<PlushGraphics::Shader> susptr = std::make_unique<PlushGraphics::Shader>();
    
    // Tester<PlushGraphics::Shader> a(std::move(susptr));

    // testFunc();

    // PlushUtil::ManagedObject<PlushGraphics::Shader> test(std::move(susptr));

    PlushGraphics::ManagedShader test(std::move(susptr));


    PlushGraphics::ManagedShader test2 = test.clone();

    // PlushGraphics::ShaderRegistry reg;

    return 0;

}
