#include "PLUSH_core_Exceptions.h"

namespace PLUSH{
    void elaborateException(Exception e){
        switch (e) {
            case ENTITY_NOT_FOUND:
                std::cout << "Crashed: Entity not found." << std::endl;
                break;
        
            case LAYER_NOT_FOUND:
                std::cout << "Crashed: Layer not found." << std::endl;
                break;

            case INSTANCE_NOT_FOUND:
                std::cout << "Crashed: Instance not found." << std::endl;
                break;
        }
    }
}