#include "DrawableIdentifier.hpp"
#include "PlushGraphicsOpenGL.hpp"

PlushGraphics::DrawableIdentifier::DrawableIdentifier()
{
    uniqueID = GlobalGraphicsState::getNextUniqueDrawableID();
}
