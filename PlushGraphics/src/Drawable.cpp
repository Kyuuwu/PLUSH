#include "Drawable/Drawable.hpp"
#include "PlushGraphics.hpp"
#include "PlushGraphicsOpenGL.hpp"
#include "Drawable/DrawableSpec.hpp"
#include "Drawable/DrawableIdentifier.hpp"

PlushGraphics::Drawable::Drawable(DrawableSpec spec)
    : modelInstance(spec.modelInstance),
      resolver(spec.resolver->duplicateSelf())
{
    
}

void PlushGraphics::Drawable::_draw() {
    // tell shader its being uniform resolved by drawable?


    modelInstance.getShader().acceptUniformResolver(resolver);
    modelInstance.draw();
}
