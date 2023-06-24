#include "Drawable.h"

namespace PLUSH {
    DrawableLayer::DrawableLayer(std::string name):
    name(name){}

    std::string DrawableLayer::getName(){
        return name;
    }

    void DrawableLayer::setName(std::string newname){
        name = newname;
    }
}