#include "../include/Drawable/DrawableIdentifier.hpp"
#include "../include/GlobalGraphicsState.hpp"

PlushGraphics::DrawableIdentifier::DrawableIdentifier()
{
    uniqueID = GlobalGraphicsState::getNextUniqueDrawableID();
}
