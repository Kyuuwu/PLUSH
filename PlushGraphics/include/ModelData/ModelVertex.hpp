#ifndef MODELVERTEX_HPP
#define MODELVERTEX_HPP

#include "PlushGraphics.hpp"
#include "OpenGL_Value.hpp"
#include <vector>

namespace PlushGraphics {
    class ModelVertex{
        public:
            std::vector<OpenGL_Value> vertexValues;
    };
}

#endif // MODELVERTEX_HPP
