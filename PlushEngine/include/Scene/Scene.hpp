#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "GraphicsLayer/ManagedGraphicsLayer.hpp"
#include "PlushGraphics.hpp"
#include "PlushEngine.hpp"
#include "SceneIdentifier.hpp"
#include "SceneSpec.hpp"

namespace PlushEngine {
    class Scene{
        public:
            using Identifier = SceneIdentifier;
            using Spec = SceneSpec;

            Scene(SceneSpec spec);

            void runLogicUpdate();

            /// wipe window and load all `Scene` `GraphicsLayers` onto the window
            void loadOntoWindow(PlushGraphics::ManagedWindow window);

            SceneIdentifier getIdentifier() const { return identifier; }

        private:
            std::vector<ManagedEntity> entities;
            std::vector<PlushGraphics::ManagedGraphicsLayer> graphicsLayers;

            SceneIdentifier identifier;
    };
}

#endif // SCENE_HPP
