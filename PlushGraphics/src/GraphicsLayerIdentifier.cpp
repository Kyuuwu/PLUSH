#include "GraphicsLayer/GraphicsLayerIdentifier.hpp"
#include "PlushGraphicsOpenGL.hpp"

PlushGraphics::GraphicsLayerIdentifier::GraphicsLayerIdentifier()
{
    uniqueID = GlobalGraphicsState::getNextUniqueGraphicsLayerID();
}

