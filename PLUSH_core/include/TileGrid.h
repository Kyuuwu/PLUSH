#include <vector>
#include <memory>
#include "ShaderUniforms.h"

namespace OPENGL_management {
    class Shader;
}

namespace PLUSH {
    class Instance;

    class TileGrid{
        public:
            TileGrid(std::shared_ptr<Instance> entity, unsigned int width = 1, unsigned int height = 1);
            TileGrid( unsigned int width = 1, unsigned int height = 1);

            void initializeGrid(std::shared_ptr<Instance> entity, unsigned int width = 1, unsigned int height = 1);

            void draw(OPENGL_management::Shader* shader, std::vector<OPENGL_management::ShaderUniform> external_uniforms);
            void draw(OPENGL_management::Shader* shader, std::vector<OPENGL_management::ShaderUniform> external_uniforms, unsigned int min_i, unsigned int max_i, unsigned int min_j, unsigned int max_j);

            void drawHighlight(OPENGL_management::Shader* shader, std::vector<OPENGL_management::ShaderUniform> external_uniforms, unsigned int i, unsigned int j);

            unsigned int getWidth();
            unsigned int getHeight();
            
            std::shared_ptr<Instance> getTile(unsigned int i, unsigned int j);

        private:
            unsigned int width;
            unsigned int height;

            std::vector<std::shared_ptr<Instance>> tiles;

            std::shared_ptr<Instance> highlighter;
    };
}