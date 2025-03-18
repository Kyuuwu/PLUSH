#ifndef GRAPHICSLAYERIDENTIFIER_HPP
#define GRAPHICSLAYERIDENTIFIER_HPP

#include "PlushGraphics.hpp"
#include "GraphicsLayer/GraphicsLayerSpec.hpp"

namespace PlushGraphics {
    class GraphicsLayerIdentifier{
        public:
            GraphicsLayerIdentifier();

            GraphicsLayerIdentifier(GraphicsLayerSpec spec):
            GraphicsLayerIdentifier()
            {
                #pragma unused(spec)
            }

            bool operator<(const GraphicsLayerIdentifier& other) const{
                return uniqueID < other.uniqueID;
            }

        private:
            graphicsLayerID_t uniqueID;
    };
}

#endif // GRAPHICSLAYERIDENTIFIER_HPP
