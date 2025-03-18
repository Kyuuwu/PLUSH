#ifndef GRAPHICSLAYERSPEC_HPP
#define GRAPHICSLAYERSPEC_HPP

#include "PlushGraphics.hpp"
#include "UniformResolver.hpp"

namespace PlushGraphics {
    class GraphicsLayerSpec{
        public:
            friend class GraphicsLayer;

            template<UniResDerived T>
            GraphicsLayerSpec(T&& ur) : 
                resolver(new T(std::move(ur))) {}

            template<UniResDerived T>
            GraphicsLayerSpec(const T& ur) : 
                resolver(new T(ur)) {}

            GraphicsLayerSpec(const GraphicsLayerSpec& other):
                resolver(other.resolver->duplicateSelf()){}

        private:
            std::unique_ptr<UniformResolver> resolver;
    };
}

#endif // GRAPHICSLAYERSPEC_HPP
