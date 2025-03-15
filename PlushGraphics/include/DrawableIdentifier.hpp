#ifndef DRAWABLEIDENTIFIER_HPP
#define DRAWABLEIDENTIFIER_HPP

#include "PlushGraphics.hpp"
#include "DrawableSpec.hpp"
#include <cstdint>

namespace PlushGraphics {
    class DrawableIdentifier{
        public:
            DrawableIdentifier();

            DrawableIdentifier(DrawableSpec spec):
                DrawableIdentifier(){
                    #pragma unused(spec)
                }

            bool operator<(const DrawableIdentifier other) const{
                return uniqueID < other.uniqueID;
            }

        private:
            drawableID_t uniqueID;
    };
}

#endif // DRAWABLEIDENTIFIER_HPP
