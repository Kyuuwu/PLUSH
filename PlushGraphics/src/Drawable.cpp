#include "Drawable.hpp"
#include "PlushGraphicsOpenGL.hpp"

void PlushGraphics::Drawable::draw() {
    resolver->resolveUniformRequirements(modelInstance.getShader());
    modelInstance.drawModel();
}
