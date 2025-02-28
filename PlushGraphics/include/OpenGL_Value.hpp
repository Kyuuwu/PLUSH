#ifndef OPENGL_VALUE_HPP
#define OPENGL_VALUE_HPP

#include "PlushGraphics.hpp"
#include "glad/glad.h"
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
            static OpenGL_Value create_uint(GLuint _u);
            static OpenGL_Value create_int(GLint _i);
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

        private:
            void checkType(OpenGL_Type _type) const;

            OpenGL_Type type;
            OpenGL_Value_Holder valueHolder;
    };
}

#endif // OPENGL_VALUE_HPP
