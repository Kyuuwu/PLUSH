#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "GraphicsLayer/ManagedGraphicsLayer.hpp"
#include "PlushGraphics.hpp"
#include "PlushEngine.hpp"

namespace PlushEngine {
    class Scene{
        public:
            void runLogicUpdate();

        private:
            std::vector<ManagedEntity> entities;
            std::vector<PlushGraphics::ManagedGraphicsLayer> graphicsLayers;
            // shaders? maybe identifiers
            std::vector<PlushGraphics::ManagedShader> shaders;
    };
}

#endif // SCENE_HPP
