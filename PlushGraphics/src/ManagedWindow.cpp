#include "PlushGraphics.hpp"
#include "Window/ManagedWindow.hpp"
#include "UniformResolvers/WindowUniformResolver.hpp"

namespace PlushGraphics {

    void ManagedWindow::runAfterCreationFromSpec(){
        UniformResolvers::WindowUniformResolver* ptr = 
            dynamic_cast<UniformResolvers::WindowUniformResolver*>((*this)->resolver.get());

        if (ptr != nullptr){
            ptr->setWindow((*this).clone());
        }
    }
    
}