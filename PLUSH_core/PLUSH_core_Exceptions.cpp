#include "PLUSH_core_Exceptions.h"

namespace PLUSH{
    void elaborateException(Exception e){
        switch (e) {
            case ENTITY_NOT_FOUND:
                std::cout << "Crashed: PLUSH_EXCEPTION: Entity not found." << std::endl;
                break;
        
            case LAYER_NOT_FOUND:
                std::cout << "Crashed: PLUSH_EXCEPTION: Layer not found." << std::endl;
                break;

            case INSTANCE_NOT_FOUND:
                std::cout << "Crashed: PLUSH_EXCEPTION: Instance not found." << std::endl;
                break;

            default:
                std::cout << "Crashed: PLUSH_EXCEPTION: Other." << std::endl;
        }
    }
}