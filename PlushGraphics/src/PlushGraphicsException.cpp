#include "PlushGraphicsException.hpp"
#include <iostream>

void PlushGraphics::describeException(PlushGraphicsException e) {
    switch(e){
        case PlushGraphicsException::FAILED_TO_CREATE_WINDOW:{
            std::cout << "Failed to create window." << std::endl;
            return;
        }
        case PlushGraphicsException::OPENGL_TYPE_NOT_FOUND:{
            std::cout << "OpenGL type not found." << std::endl;
            return;
        }
        case PlushGraphicsException::OPENGL_VALUE_GET_INVALID_TYPE:{
            std::cout << "Attempted to retrieve value of invalid type from OpenGL_Value." << std::endl;
            return;
        }
        case PlushGraphicsException::SHADER_AND_MODELDATA_INCOMPATIBLE:{
            std::cout << "Provided Shader and ModelData are incompatible to create ModelInstance." << std::endl;
            return;
        }
        case PlushGraphicsException::MODELDATA_HAS_DUPLICATE_TARGET_SLOT:{
            std::cout << "ModelData has a duplicate target slot." << std::endl;
            return;
        }
        case PlushGraphicsException::VECTOR_INDEX_OUT_OF_BOUNDS:{
            std::cout << "OpenGL_Value vector subvalue index is out of bounds." << std::endl;
            return;
        }
        case PlushGraphicsException::UNIFORM_PAYLOAD_TYPES_DONT_MATCH:{
            std::cout << "Uniform payload types (Slot identifier type and OpenGL_Value type) don't match." << std::endl;
            return;
        }
        case PlushGraphicsException::CANNOT_CHANGE_DRAWABLE_SHADER:{
            std::cout << "Changing ModelInstance of Drawable is not permitted to change the Drawable's targeted Shader ." << std::endl;
            return;
        }
        default:{
            std::cout << "This PlushGraphics exception is not documented, requires update to describeException(PlushGraphicsException e)." << std::endl;
            return;
        }
    }
}
