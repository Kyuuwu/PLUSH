#ifndef GRAPHICSLAYER_HPP
#define GRAPHICSLAYER_HPP

#include "PlushGraphics.hpp"
#include <vector>

namespace PlushGraphics{
    class GraphicsLayer{
        public:
            GraphicsLayer();
            
            void draw();

        private:
            SharedPtrUniformResolver resolver;

            std::vector<ManagedDrawable> drawables;
    };
}

#endif // GRAPHICSLAYER_HPP
