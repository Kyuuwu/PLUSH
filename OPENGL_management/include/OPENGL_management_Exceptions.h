#ifndef OPENGL_MANAGEMENT_EXCEPTIONS
#define OPENGL_MANAGEMENT_EXCEPTIONS
#include <iostream>

namespace OPENGL_management {
    enum Exception{
        WINDOW_NOT_ACTIVE,
        WINDOW_NOT_CLOSED,
        INVALID_UNIFORM_TYPE,
        INVALID_INPUT_TYPE,
        INVALID_TYPE,
        INPUT_TYPE_NOT_FOUND,
        MATCHING_UNIFORM_SLOT_NOT_FOUND,
        SHADER_COMPILE_MISSING_UNIFORM_SLOT,
        MODEL_NOT_FOUND,
        TEXTURE2D_NOT_FOUND,
        SHADER_NOT_FOUND,
        INVALID_DEFAULT_CODE,
        ADD_UNIFORM_ERROR
    };

    inline void elaborateException(Exception e){
        std::cout << "Code: " << (int) e << std::endl;
    }
}

#endif