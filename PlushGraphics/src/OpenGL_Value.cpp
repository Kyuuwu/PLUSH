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
        return value;
    }

    OpenGL_Value OpenGL_Value::create_int(GLint _i) {
        OpenGL_Value value;
        value.type = OpenGL_Type::INT;
        value.valueHolder.i = _i;
        return value;
    }

    OpenGL_Value OpenGL_Value::create_sampler_2D(GLint _i) {
        OpenGL_Value value;
        value.type = OpenGL_Type::SAMPLER2D;
        value.valueHolder.i = _i;
        return value;
    }

    OpenGL_Value OpenGL_Value::create_float(GLfloat _f) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT;
        value.valueHolder.f = _f;
        return value;
    }

    OpenGL_Value OpenGL_Value::create_vec2(glm::vec2 _v2) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT_VEC_2;
        value.valueHolder.v2 = _v2;
        return value;
    }

    OpenGL_Value OpenGL_Value::create_vec3(glm::vec3 _v3) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT_VEC_3;
        value.valueHolder.v3 = _v3;
        return value;
    }

    OpenGL_Value OpenGL_Value::create_vec4(glm::vec4 _v4) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT_VEC_4;
        value.valueHolder.v4 = _v4;
        return value;
    }

    OpenGL_Value OpenGL_Value::create_mat2(glm::mat2 _m2) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT_MAT_2;
        value.valueHolder.m2 = _m2;
        return value;
    }

    OpenGL_Value OpenGL_Value::create_mat3(glm::mat3 _m3) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT_MAT_3;
        value.valueHolder.m3 = _m3;
        return value;
    }

    OpenGL_Value OpenGL_Value::create_mat4(glm::mat4 _m4) {
        OpenGL_Value value;
        value.type = OpenGL_Type::FLOAT_MAT_4;
        value.valueHolder.m4 = _m4;
        return value;
    }

    OpenGL_Value OpenGL_Value::readFromStringstream(std::stringstream& stream, OpenGL_Type _type) {
        switch (_type) {
            case OpenGL_Type::UINT:{
                GLuint u;
                stream >> u;
                return create_uint(u);
            }

            case OpenGL_Type::INT:{
                GLint i;
                stream >> i;
                return create_int(i);
            }

            case OpenGL_Type::FLOAT:{
                GLfloat f;
                stream >> f;
                return create_float(f);
            }

            case OpenGL_Type::FLOAT_VEC_2:{
                GLfloat f1,f2;
                stream >> f1;
                stream >> f2;
                return create_vec2(glm::vec2(f1,f2));
            }

            case OpenGL_Type::FLOAT_VEC_3:{
                GLfloat f1,f2, f3;
                stream >> f1;
                stream >> f2;
                stream >> f3;
                return create_vec3(glm::vec3(f1,f2,f3));
            }

            case OpenGL_Type::FLOAT_VEC_4:{
                GLfloat f1,f2, f3, f4;
                stream >> f1;
                stream >> f2;
                stream >> f3;
                stream >> f4;
                return create_vec4(glm::vec4(f1,f2,f3,f4));
            }

            default:
                std::cout << "Error: OpenGL_Value reading from stringstream not implemented for type " << getStringFromType(_type) << std::endl;
                throw(PlushGraphicsException::OPENGL_TYPE_NOT_FOUND);
        }
    }

    GLuint OpenGL_Value::get_uint() const {
        checkType(OpenGL_Type::UINT);
        return valueHolder.u;
    }

    GLint OpenGL_Value::get_int() const {
        checkType(OpenGL_Type::INT);
        return valueHolder.i;
    }

    GLint OpenGL_Value::get_sampler_2D() const {
        checkType(OpenGL_Type::SAMPLER2D);
        return valueHolder.i;
    }

    GLfloat OpenGL_Value::get_float() const {
        checkType(OpenGL_Type::FLOAT);
        return valueHolder.f;
    }

    GLfloat* OpenGL_Value::get_vec2_ptr() {
        checkType(OpenGL_Type::FLOAT_VEC_2);
        return glm::value_ptr(valueHolder.v2);
    }

    GLfloat OpenGL_Value::get_vec2_subvalue(uint16_t index) const {
        checkType(OpenGL_Type::FLOAT_VEC_2);
        switch (index) {
            case 0:
                return valueHolder.v2.x;
            case 1:
                return valueHolder.v2.y;
            default:
                throw(PlushGraphicsException::VECTOR_INDEX_OUT_OF_BOUNDS);
        }
    }

    GLfloat* OpenGL_Value::get_vec3_ptr() {
        checkType(OpenGL_Type::FLOAT_VEC_3);
        return glm::value_ptr(valueHolder.v3);
    }

    GLfloat OpenGL_Value::get_vec3_subvalue(uint16_t index) const {
        checkType(OpenGL_Type::FLOAT_VEC_3);
        switch (index) {
            case 0:
                return valueHolder.v3.x;
            case 1:
                return valueHolder.v3.y;
            case 2:
                return valueHolder.v3.z;
            default:
                throw(PlushGraphicsException::VECTOR_INDEX_OUT_OF_BOUNDS);
        }
    }

    GLfloat* OpenGL_Value::get_vec4_ptr() {
        checkType(OpenGL_Type::FLOAT_VEC_4);
        return glm::value_ptr(valueHolder.v4);
    }

    GLfloat OpenGL_Value::get_vec4_subvalue(uint16_t index) const {
        checkType(OpenGL_Type::FLOAT_VEC_4);
        switch (index) {
            case 0:
                return valueHolder.v4.x;
            case 1:
                return valueHolder.v4.y;
            case 2:
                return valueHolder.v4.z;
            case 3:
                return valueHolder.v4.w;
            default:
                throw(PlushGraphicsException::VECTOR_INDEX_OUT_OF_BOUNDS);
        }
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

    void OpenGL_Value::checkType(OpenGL_Type _type) const {
        if(type != _type){
            std::cout << "Error: attempting to get value of type " << getStringFromType(_type) << " from OpenGL_Value object of type " << getStringFromType(type) << std::endl;
            throw(PlushGraphics::PlushGraphicsException::OPENGL_VALUE_GET_INVALID_TYPE);
        }
    }

}