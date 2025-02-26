#ifndef MODELVERTEX_HPP
#define MODELVERTEX_HPP

#include "PlushGraphics.hpp"
#include "ShaderUniformPayload.hpp"
#include <vector>

namespace PlushGraphics {
    class ModelVertex{
        public:
            std::vector<ShaderMetadata::ShaderUniformPayload> vertexValues;
    };
}

#endif // MODELVERTEX_HPP
