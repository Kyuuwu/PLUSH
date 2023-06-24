#ifndef SHADER_UNIFORMS
#define SHADER_UNIFORMS

#include <string>
#include <glm/glm.hpp>

namespace OPENGL_management {
    enum GL_type{
        OPENGL_INT,
        OPENGL_UINT,
        OPENGL_FLOAT,
        OPENGL_FLOAT_MAT_2,
        OPENGL_FLOAT_MAT_3,
        OPENGL_FLOAT_MAT_4,
        OPENGL_FLOAT_VEC_2,
        OPENGL_FLOAT_VEC_3,
        OPENGL_FLOAT_VEC_4,
        OPENGL_SAMPLER2D
    };

    struct TextureNamePair{
        std::string uniformname;
        std::string texturename;
    };

    union ShaderUniformValue{
        int i;
        unsigned int u;
        float f;
        void* fptr;
    };

    struct ShaderUniformTarget{
        std::string name;
        GL_type type;
    };

    struct ShaderUniformSlot{
        std::string name;
        int location;
        GL_type type;
        bool isSet = false;
        ShaderUniformValue defaultValue;
    };

    struct ShaderInput{
        std::string name;
        int location;
        GL_type type;
    };
    struct ShaderUniform{
        ShaderUniformTarget target;
        ShaderUniformValue value;
    };

    GL_type getTypeFromString(std::string typestring);
    bool isSameSlot(ShaderUniformSlot &a, ShaderUniformSlot &b);

    enum Mat2_Default{
        MAT2_IDENTITY
    };

    enum Mat3_Default{
        MAT3_IDENTITY
    };

    enum Mat4_Default{
        MAT4_IDENTITY
    };

    enum Vec2_Default{
        VEC2_ZERO
    };

    enum Vec3_Default{
        VEC3_ZERO
    };

    enum Vec4_Default{
        VEC4_ZERO,
        VEC4_RED,
        VEC4_GREEN,
        VEC4_BLUE
    };

    class ShaderUniformDefaults{
        public:
            static ShaderUniformValue getDefaultValue(GL_type type, unsigned int defaultCode);
            static ShaderUniformValue getVec2DefaultValue(Vec2_Default defaultCode);
            static ShaderUniformValue getVec3DefaultValue(Vec3_Default defaultCode);
            static ShaderUniformValue getVec4DefaultValue(Vec4_Default defaultCode);
            static ShaderUniformValue getMat4DefaultValue(Mat4_Default defaultCode);

        private:
            inline static glm::vec2 zero2 = glm::vec2(0.0f);
            inline static glm::vec3 zero3 = glm::vec3(0.0f);

            inline static glm::vec4 zero4 = glm::vec4(0.0f);
            inline static glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
            inline static glm::vec4 green = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
            inline static glm::vec4 blue = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

            inline static glm::mat2 identity2 = glm::mat2(1.0f);
            inline static glm::mat3 identity3 = glm::mat3(1.0f);
            inline static glm::mat4 identity4 = glm::mat4(1.0f);
    };
}

#endif