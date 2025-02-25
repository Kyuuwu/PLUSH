#include "OpenGL_Value.hpp"
#include "OpenGL_Type.hpp"
#include "PlushGraphicsException.hpp"
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace PlushGraphics {

    OpenGL_Value OpenGL_Value::create_uint(GLuint _u) {
        OpenGL_Value value;
        value.type = OpenGL_Type::UINT;
        value.valueHolder.u = _u;
    }

    OpenGL_Value OpenGL_Value::create_int(GLint _i) {
        OpenGL_Value value;
        value.type = OpenGL_Type::INT;
        value.valueHolder.i = _i;
    }

    OpenGL_Value OpenGL_Value::create_float(GLfloat _f) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT;
        value.valueHolder.f = _f;
    }

    OpenGL_Value OpenGL_Value::create_vec2(glm::vec2 _v2) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT_VEC_2;
        value.valueHolder.v2 = _v2;
    }

    OpenGL_Value OpenGL_Value::create_vec3(glm::vec3 _v3) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT_VEC_3;
        value.valueHolder.v3 = _v3;
    }

    OpenGL_Value OpenGL_Value::create_vec4(glm::vec4 _v4) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT_VEC_4;
        value.valueHolder.v4 = _v4;
    }

    OpenGL_Value OpenGL_Value::create_mat2(glm::mat2 _m2) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT_MAT_2;
        value.valueHolder.m2 = _m2;
    }

    OpenGL_Value OpenGL_Value::create_mat3(glm::mat3 _m3) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT_MAT_3;
        value.valueHolder.m3 = _m3;
    }

    OpenGL_Value OpenGL_Value::create_mat4(glm::mat4 _m4) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT_MAT_4;
        value.valueHolder.m4 = _m4;
    }

    GLuint OpenGL_Value::get_uint() {
        checkType(OpenGL_Type::UINT);
        return valueHolder.u;
    }

    GLint OpenGL_Value::get_int() {
        checkType(OpenGL_Type::INT);
        return valueHolder.i;
    }

    GLfloat OpenGL_Value::get_float() {
        checkType(OpenGL_Type::FLOAT);
        return valueHolder.f;
    }

    GLfloat* OpenGL_Value::get_vec2_ptr() {
        checkType(OpenGL_Type::FLOAT_VEC_2);
        return glm::value_ptr(valueHolder.v2);
    }

    GLfloat* OpenGL_Value::get_vec3_ptr() {
        checkType(OpenGL_Type::FLOAT_VEC_3);
        return glm::value_ptr(valueHolder.v3);
    }

    GLfloat* OpenGL_Value::get_vec4_ptr() {
        checkType(OpenGL_Type::FLOAT_VEC_4);
        return glm::value_ptr(valueHolder.v4);
    }

    GLfloat* OpenGL_Value::get_mat2_ptr() {
        checkType(OpenGL_Type::FLOAT_MAT_2);
        return glm::value_ptr(valueHolder.m2);
    }

    GLfloat* OpenGL_Value::get_mat3_ptr() {
        checkType(OpenGL_Type::FLOAT_MAT_3);
        return glm::value_ptr(valueHolder.m3);
    }

    GLfloat* OpenGL_Value::get_mat4_ptr() {
        checkType(OpenGL_Type::FLOAT_MAT_4);
        return glm::value_ptr(valueHolder.m4);
    }

    void OpenGL_Value::checkType(OpenGL_Type _type) {
        if(type != _type){
            std::cout << "Error: attempting to get value of type " << getStringFromType(_type) << " from OpenGL_Value object of type " << getStringFromType(type) << std::endl;
            throw(PlushGraphics::PlushGraphicsException::OPENGL_VALUE_GET_INVALID_TYPE);
        }
    }

}