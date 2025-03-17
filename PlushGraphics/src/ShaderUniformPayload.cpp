#include "Shader/ShaderUniformPayload.hpp"
#include "Shader/ShaderUniformSlot.hpp"
#include "OpenGL_Type.hpp"
#include "PlushGraphicsException.hpp"

namespace PlushGraphics {
    void ShaderMetadata::ShaderUniformPayload::setUniformAtSlot(ShaderUniformSlot& slot) {
        setUniformAtLocation(slot.location);
        slot.fulfillmentState = fulfillmentData;
    }

    void ShaderMetadata::ShaderUniformPayload::setUniformAtLocation(shaderSlotLocation_t location){
        switch(value.getType()){
            case PlushGraphics::OpenGL_Type::UINT:
                glUniform1ui(location, value.get_uint());
                return;

            case PlushGraphics::OpenGL_Type::INT:
                glUniform1i(location, value.get_int());
                return;

            case PlushGraphics::OpenGL_Type::FLOAT:
                glUniform1f(location, value.get_float());
                return;
                
            case PlushGraphics::OpenGL_Type::FLOAT_VEC_2:
                glUniform2fv(location, 1, value.get_vec2_ptr());
                return;
                
            case PlushGraphics::OpenGL_Type::FLOAT_VEC_3:
                glUniform3fv(location, 1, value.get_vec3_ptr());
                return;
                
            case PlushGraphics::OpenGL_Type::FLOAT_VEC_4:
                glUniform4fv(location, 1, value.get_vec4_ptr());
                return;
                
            case PlushGraphics::OpenGL_Type::FLOAT_MAT_2:
                glUniformMatrix2fv(location, 1, GL_FALSE, value.get_mat2_ptr());
                return;
                
            case PlushGraphics::OpenGL_Type::FLOAT_MAT_3:
                glUniformMatrix3fv(location, 1, GL_FALSE, value.get_mat3_ptr());
                return;
            
            case PlushGraphics::OpenGL_Type::FLOAT_MAT_4:
                glUniformMatrix4fv(location, 1, GL_FALSE, value.get_mat4_ptr());
                return;

            case PlushGraphics::OpenGL_Type::SAMPLER2D:
                glUniform1i(location, value.get_sampler_2D());
                return;
            
            default:
                std::cout << "Error: cannot set uniform of type " << getStringFromType(value.getType()) << std::endl;
                throw(PlushGraphicsException::OPENGL_TYPE_NOT_FOUND);
        }
    }
}