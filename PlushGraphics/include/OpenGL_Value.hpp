#ifndef OPENGL_VALUE_HPP
#define OPENGL_VALUE_HPP

#include "OpenGL_Type.hpp"
#include "PlushGraphics.hpp"
#include "OpenGL.h"
#include "glm/glm.hpp"
#include <sstream>

namespace PlushGraphics {

    union OpenGL_Value_Holder{
        GLuint u;
        GLint i;
        GLfloat f;
        glm::vec2 v2;
        glm::vec3 v3;
        glm::vec4 v4;
        glm::mat2 m2;
        glm::mat3 m3;
        glm::mat4 m4;
    };

    class OpenGL_Value{
        public:
            // OpenGL_Value(const OpenGL_Value& other)
            // {
            //     (*this)=other;
            // }

            // OpenGL_Value& operator=(const OpenGL_Value& other){
            //     type = other.type;

            //     switch (type) {
            //         case PlushGraphics::OpenGL_Type::UINT:
            //             valueHolder.u = other.get_uint();
            //             return *this;
            //         case PlushGraphics::OpenGL_Type::INT:
            //             valueHolder.i = other.get_int();
            //             return *this;
            //         case PlushGraphics::OpenGL_Type::FLOAT:
            //             valueHolder.f = other.get_float();
            //             return *this;
            //         case PlushGraphics::OpenGL_Type::FLOAT_VEC_2:
            //             valueHolder.v2 = other.valueHolder.v2;
            //             return *this;
            //         case PlushGraphics::OpenGL_Type::FLOAT_VEC_3:
            //             valueHolder.v3 = other.valueHolder.v3;
            //             return *this;
            //         case PlushGraphics::OpenGL_Type::FLOAT_VEC_4:
            //             valueHolder.v4 = other.valueHolder.v4;
            //             return *this;
            //         case PlushGraphics::OpenGL_Type::FLOAT_MAT_2:
            //             valueHolder.m2 = other.valueHolder.m2;
            //             return *this;
            //         case PlushGraphics::OpenGL_Type::FLOAT_MAT_3:
            //             valueHolder.m3 = other.valueHolder.m3;
            //             return *this;
            //         case PlushGraphics::OpenGL_Type::FLOAT_MAT_4:
            //             valueHolder.m4 = other.valueHolder.m4;
            //             return *this;
            //         case PlushGraphics::OpenGL_Type::SAMPLER2D:
            //             valueHolder.i = other.valueHolder.i;
            //             return *this;
            //     }

            //     return *this;
            // }

            static OpenGL_Value create_uint(GLuint _u);
            static OpenGL_Value create_int(GLint _i);
            static OpenGL_Value create_sampler_2D(GLint _i);
            static OpenGL_Value create_float(GLfloat _f);
            static OpenGL_Value create_vec2(glm::vec2 _v2);
            static OpenGL_Value create_vec3(glm::vec3 _v3);
            static OpenGL_Value create_vec4(glm::vec4 _v4);
            static OpenGL_Value create_mat2(glm::mat2 _m2);
            static OpenGL_Value create_mat3(glm::mat3 _m3);
            static OpenGL_Value create_mat4(glm::mat4 _m4);

            static OpenGL_Value readFromStringstream(std::stringstream& stream, OpenGL_Type _type);

            GLuint get_uint() const;
            GLint get_int() const;
            GLint get_sampler_2D() const;
            GLfloat get_float() const;
            GLfloat* get_vec2_ptr();
            GLfloat get_vec2_subvalue(uint16_t index) const;
            GLfloat* get_vec3_ptr();
            GLfloat get_vec3_subvalue(uint16_t index) const;
            GLfloat* get_vec4_ptr();
            GLfloat get_vec4_subvalue(uint16_t index) const;
            GLfloat* get_mat2_ptr();
            GLfloat* get_mat3_ptr();
            GLfloat* get_mat4_ptr();

            OpenGL_Type getType() const { return type; }

            bool operator==(const OpenGL_Value& other){
                if(type == other.type){
                    switch (type) {
                        case PlushGraphics::OpenGL_Type::UINT:
                            return get_uint() == other.get_uint();
                        case PlushGraphics::OpenGL_Type::INT:
                            return get_int() == other.get_int();
                        case PlushGraphics::OpenGL_Type::FLOAT:
                            return get_float() == other.get_float();
                        case PlushGraphics::OpenGL_Type::FLOAT_VEC_2:
                            return valueHolder.v2 == other.valueHolder.v2;
                        case PlushGraphics::OpenGL_Type::FLOAT_VEC_3:
                            return valueHolder.v3 == other.valueHolder.v3;
                        case PlushGraphics::OpenGL_Type::FLOAT_VEC_4:
                            return valueHolder.v4 == other.valueHolder.v4;
                        case PlushGraphics::OpenGL_Type::FLOAT_MAT_2:
                            return valueHolder.m2 == other.valueHolder.m2;
                        case PlushGraphics::OpenGL_Type::FLOAT_MAT_3:
                            return valueHolder.m3 == other.valueHolder.m3;
                        case PlushGraphics::OpenGL_Type::FLOAT_MAT_4:
                            return valueHolder.m4 == other.valueHolder.m4;
                        case PlushGraphics::OpenGL_Type::SAMPLER2D:
                            return get_sampler_2D() == other.get_sampler_2D();
                    }
                }else{
                    return false;
                }
            }

        private:
            OpenGL_Value():
            type(OpenGL_Type::UINT)
            {}

            void checkType(OpenGL_Type _type) const;

            OpenGL_Type type;
            OpenGL_Value_Holder valueHolder;
    };
}

#endif // OPENGL_VALUE_HPP
