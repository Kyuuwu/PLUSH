#ifndef GRAPHICSLAYER_HPP
#define GRAPHICSLAYER_HPP

#include "PlushGraphics.hpp"
#include <set>
#include <vector>
#include "GraphicsLayer/GraphicsLayerIdentifier.hpp"

namespace PlushGraphics{
    class GraphicsLayer{
        public:
            using Spec = GraphicsLayerSpec;
            using Identifier = GraphicsLayerIdentifier;

            GraphicsLayer(GraphicsLayerSpec spec);
            
            void _performDrawCycle();

            void _addDrawable(ManagedDrawable drawable);

            GraphicsLayerIdentifier getIdentifier(){
                return identifier;
            }

        private:
            GraphicsLayerIdentifier identifier;

            std::set<ManagedShader> getNecessaryShaders();

            std::set<ManagedShader> getNecessaryShadersFromDrawables();

            SharedPtrUniformResolver resolver;

            std::vector<ManagedDrawable> drawables;
    };
}

#endif // GRAPHICSLAYER_HPP
