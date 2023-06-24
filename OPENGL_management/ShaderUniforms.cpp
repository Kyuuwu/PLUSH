#include "OPENGL_management_includes.h"
#include <iostream>

namespace OPENGL_management {
    bool isSameSlot(ShaderUniformSlot &a, ShaderUniformSlot &b){
        if(a.type != b.type) return false;
        if(a.location != b.location) return false;
        if(a.name != b.name) return false;
        return true;
    }

    GL_type getTypeFromString(std::string typestring){
        if (typestring == "uint"){
            return OPENGL_UINT;
        }
        if (typestring == "int"){
            return OPENGL_INT;
        }
        if (typestring == "float"){
            return OPENGL_FLOAT;
        }
        if (typestring == "vec2"){
            return OPENGL_FLOAT_VEC_2;
        }
        if (typestring == "vec3"){
            return OPENGL_FLOAT_VEC_3;
        }
        if (typestring == "vec4"){
            return OPENGL_FLOAT_VEC_4;
        }
        if (typestring == "mat2"){
            return OPENGL_FLOAT_MAT_2;
        }
        if (typestring == "mat3"){
            return OPENGL_FLOAT_MAT_3;
        }
        if (typestring == "mat4"){
            return OPENGL_FLOAT_MAT_4;
        }
        if (typestring == "sampler2D"){
            return OPENGL_SAMPLER2D;
        }

        std::cout << "Error: Input type " << typestring << " was not found during conversion from string to GL_type." << std::endl;

        throw(INPUT_TYPE_NOT_FOUND);
    }

    ShaderUniformValue ShaderUniformDefaults::getDefaultValue(GL_type type, unsigned int defaultCode){
        switch (type) {
            case OPENGL_FLOAT_VEC_2:{
                Vec2_Default vec2DefaultCode = (Vec2_Default)(VEC2_ZERO + defaultCode);
                return getVec2DefaultValue(vec2DefaultCode);
            }

            case OPENGL_FLOAT_VEC_3:{
                Vec3_Default vec3DefaultCode = (Vec3_Default)(VEC3_ZERO + defaultCode);
                return getVec3DefaultValue(vec3DefaultCode);
            }

            case OPENGL_FLOAT_VEC_4:{
                Vec4_Default vec4DefaultCode = (Vec4_Default)(VEC4_ZERO + defaultCode);
                return getVec4DefaultValue(vec4DefaultCode);
            }

            case OPENGL_FLOAT_MAT_4:{
                Mat4_Default mat4DefaultCode = (Mat4_Default)(MAT4_IDENTITY + defaultCode);
                return getMat4DefaultValue(mat4DefaultCode);
            }
                
            case OPENGL_SAMPLER2D:{
                ShaderUniformValue value;
                value.i = defaultCode;
                return value;
            }

            default:
                throw(INVALID_UNIFORM_TYPE);            
        }
    }

    ShaderUniformValue ShaderUniformDefaults::getMat4DefaultValue(Mat4_Default defaultCode){
        ShaderUniformValue value;
        switch(defaultCode){
            case MAT4_IDENTITY:
                value.fptr = &identity4[0][0];
                break;
            
            default:
                throw(INVALID_DEFAULT_CODE);
        }

        return value;
    }

    ShaderUniformValue ShaderUniformDefaults::getVec2DefaultValue(Vec2_Default defaultCode){
        ShaderUniformValue value;
        switch(defaultCode){
            case VEC2_ZERO:
                value.fptr = &zero3[0];
                break;

            default:
                throw(INVALID_DEFAULT_CODE);
        }

        return value;
    }

    ShaderUniformValue ShaderUniformDefaults::getVec3DefaultValue(Vec3_Default defaultCode){
        ShaderUniformValue value;
        switch(defaultCode){
            case VEC3_ZERO:
                value.fptr = &zero3[0];
                break;

            default:
                throw(INVALID_DEFAULT_CODE);
        }

        return value;
    }

    ShaderUniformValue ShaderUniformDefaults::getVec4DefaultValue(Vec4_Default defaultCode){
        ShaderUniformValue value;
        switch(defaultCode){
            case VEC4_ZERO:
                value.fptr = &zero4[0];
                break;

            case VEC4_RED:
                value.fptr = &red[0];
                break;

            case VEC4_GREEN:
                value.fptr = &green[0];
                break;

            case VEC4_BLUE:
                value.fptr = &blue[0];
                break;

            default:
                throw(INVALID_DEFAULT_CODE);
        }

        return value;
    }
}