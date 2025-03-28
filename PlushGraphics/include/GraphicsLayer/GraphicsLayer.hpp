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

            void _removeDrawable(ManagedDrawable drawable);

            GraphicsLayerIdentifier getIdentifier(){
                return identifier;
            }

            std::set<ManagedShader> _getNecessaryShaders();

        private:
            GraphicsLayerIdentifier identifier;

            std::set<ManagedShader> getNecessaryShadersFromDrawables();

            SharedPtrUniformResolver resolver;

            std::vector<ManagedDrawable> drawables;
    };
}

#endif // GRAPHICSLAYER_HPP
