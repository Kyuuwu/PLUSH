#include "OpenGL_Type.hpp"
#include "PlushGraphicsException.hpp"
#include "OpenGL.h"

PlushGraphics::OpenGL_Type PlushGraphics::getTypeFromString(std::string typestring){
    if (typestring == "uint"){
        return OpenGL_Type::UINT;
    }
    if (typestring == "int"){
        return OpenGL_Type::INT;
    }
    if (typestring == "float"){
        return OpenGL_Type::FLOAT;
    }
    if (typestring == "vec2"){
        return OpenGL_Type::FLOAT_VEC_2;
    }
    if (typestring == "vec3"){
        return OpenGL_Type::FLOAT_VEC_3;
    }
    if (typestring == "vec4"){
        return OpenGL_Type::FLOAT_VEC_4;
    }
    if (typestring == "mat2"){
        return OpenGL_Type::FLOAT_MAT_2;
    }
    if (typestring == "mat3"){
        return OpenGL_Type::FLOAT_MAT_3;
    }
    if (typestring == "mat4"){
        return OpenGL_Type::FLOAT_MAT_4;
    }
    if (typestring == "sampler2D"){
        return OpenGL_Type::SAMPLER2D;
    }

    std::cout << "Error: Input type " << typestring << " was not found during conversion from string to GL_type." << std::endl;

    throw(PlushGraphicsException::OPENGL_TYPE_NOT_FOUND);
}

std::string PlushGraphics::getStringFromType(OpenGL_Type type){
    switch (type) {
        case OpenGL_Type::UINT:{
            return "uint";
        }
        case OpenGL_Type::INT:{
            return "int";
        }
        case OpenGL_Type::FLOAT:{
            return "float";
        }
        case OpenGL_Type::FLOAT_VEC_2:{
            return "vec2";
        }
        case OpenGL_Type::FLOAT_VEC_3:{
            return "vec3";
        }
        case OpenGL_Type::FLOAT_VEC_4:{
            return "vec4";
        }
        case OpenGL_Type::FLOAT_MAT_2:{
            return "mat2";
        }
        case OpenGL_Type::FLOAT_MAT_3:{
            return "mat3";
        }
        case OpenGL_Type::FLOAT_MAT_4:{
            return "mat4";
        }
        case OpenGL_Type::SAMPLER2D:{
            return "sampler2D";
        }
        default:
            std::cout << "Error: Input type code" << (unsigned int)type << " was not found during conversion from GL_type to string." << std::endl;

            throw(PlushGraphicsException::OPENGL_TYPE_NOT_FOUND);
    }

    
}
size_t PlushGraphics::getSizeOf(OpenGL_Type type) {
    
    switch (type) {
        case OpenGL_Type::UINT:{
            return sizeof(GLuint);
        }
        case OpenGL_Type::INT:{
            return sizeof(GLint);
        }
        case OpenGL_Type::FLOAT:{
            return sizeof(GLfloat);
        }
        case OpenGL_Type::FLOAT_VEC_2:{
            return 2*sizeof(GLfloat);
        }
        case OpenGL_Type::FLOAT_VEC_3:{
            return 3*sizeof(GLfloat);
        }
        case OpenGL_Type::FLOAT_VEC_4:{
            return 4*sizeof(GLfloat);
        }
        case OpenGL_Type::FLOAT_MAT_2:{
            return 4*sizeof(GLfloat);
        }
        case OpenGL_Type::FLOAT_MAT_3:{
            return 9*sizeof(GLfloat);
        }
        case OpenGL_Type::FLOAT_MAT_4:{
            return 16*sizeof(GLfloat);
        }
        default:
            std::cout << "Error: Input type code" << (unsigned int)type << " not supported for sizeof operation." << std::endl;

            throw(PlushGraphicsException::OPENGL_TYPE_NOT_FOUND);
    }
}
