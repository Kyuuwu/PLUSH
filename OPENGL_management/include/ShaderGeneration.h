namespace OPENGL_management {
    class Shader;
    
    class ShaderGeneration{
        public:
            static Shader* generateShaderFromFiles(const char* vertexPath, const char* fragmentPath, const char *name);
            static Shader* generateShaderFromComboFile(const char* comboPath);
    };
}