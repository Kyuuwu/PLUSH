#ifndef OPENGL_TYPE_HPP
#define OPENGL_TYPE_HPP

#include <string>
#include <iostream>

namespace PlushGraphics {
    enum class OpenGL_Type{
        INT,
        UINT,
        FLOAT,
        FLOAT_MAT_2,
        FLOAT_MAT_3,
        FLOAT_MAT_4,
        FLOAT_VEC_2,
        FLOAT_VEC_3,
        FLOAT_VEC_4,
        SAMPLER2D
    };

    OpenGL_Type getTypeFromString(std::string typestring);
    std::string getStringFromType(OpenGL_Type type);
    size_t getSizeOf(OpenGL_Type type);
}

#endif // OPENGL_TYPE_HPP
