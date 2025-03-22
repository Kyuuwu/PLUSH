#include "GraphicsLayer/GraphicsLayerIdentifier.hpp"
#include "../include/GlobalGraphicsState.hpp"

PlushGraphics::GraphicsLayerIdentifier::GraphicsLayerIdentifier()
{
    uniqueID = GlobalGraphicsState::getNextUniqueGraphicsLayerID();
}

