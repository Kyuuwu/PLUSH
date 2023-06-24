#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include "ShaderUniforms.h"
#include "Drawable.h"

namespace OPENGL_management{
    class Shader;
}

namespace PLUSH {
    class TileGrid;
    class Entity;

    struct CoordPair{
        int i = 0;
        int j = 0;
    };

    class TileGridLayer : public DrawableLayer{
        public:
            TileGridLayer(std::string name = "Default_tilegrid_layer_name:FIX_THIS");

            void draw(std::vector<OPENGL_management::ShaderUniform> external_uniforms = std::vector<OPENGL_management::ShaderUniform>()) override;

            void setTileGrid(std::shared_ptr<TileGrid> newTileGrid);

            void snapToEdges_IfOutOfBounds();

            void incrementOffset(float x, float y);

            void setOffset(float x, float y);
            void setDimensions(float x, float y);
            void setTileDimensions(float x, float y);
            void setPosition(float x, float y);

            float getOffsetX();
            float getOffsetY();

            void addMoveable(std::shared_ptr<Entity> moveable);
            std::vector<std::shared_ptr<Entity>> getMoveables();
            void setMoveablePosition(std::string moveableName, glm::vec2 position);
            void setMoveablePosition(std::string moveableName, float x, float y);

            void setHighlights(std::vector<CoordPair> newhighlights);
            void resetHighlights();
            void addHighlight(unsigned int i, unsigned int j);

        private:
            std::shared_ptr<OPENGL_management::Shader> tilegridshader;
            std::shared_ptr<OPENGL_management::Shader> moveableshader;

            std::shared_ptr<TileGrid> tilegrid;

            std::vector<std::shared_ptr<Entity>> moveables;

            std::vector<CoordPair> highlights;

            glm::vec2 dimensions = glm::vec2(1.0f, 1.05f);
            glm::vec2 position = glm::vec2(-0.25f, -0.5f);
            glm::vec2 tileDimensions = glm::vec2(0.1f, 0.15f);
            glm::vec2 offset = glm::vec2(0.0f, 0.0f);

            void generateUniforms();
            std::vector<OPENGL_management::ShaderUniform> uniforms;
            bool uniforms_up_to_date = false;
    };
}