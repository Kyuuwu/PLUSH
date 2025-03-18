#ifndef GRAPHICSLAYERREGISTRY_HPP
#define GRAPHICSLAYERREGISTRY_HPP

#include "PlushGraphics.hpp"
#include "Registry.hpp"
#include "ManagedGraphicsLayer.hpp"

namespace PlushGraphics {
    class GraphicsLayerRegistry : public PlushUtil::Registry<ManagedGraphicsLayer>{
    };
}

#endif // GRAPHICSLAYERREGISTRY_HPP
