#include "Drawable.hpp"
#include "PlushGraphicsOpenGL.hpp"

void PlushGraphics::Drawable::draw() {
    modelInstance.getShader().acceptUniformResolver(resolver);
    modelInstance.draw();
}
