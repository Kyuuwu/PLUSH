#ifndef NOOPRESOLVER_HPP
#define NOOPRESOLVER_HPP

#include "PlushGraphics.hpp"
#include "UniformResolver.hpp"

namespace PlushGraphics {
    namespace UniformResolvers { // various PlushGraphics-level uniform resolvers
        class NoOpResolver : public UniformResolver{ // no-op resolver, does not attempt to resolve uniforms
            public:
                UniquePtrUniformResolver duplicateSelf() const override {
                    return UniquePtrUniformResolver(new NoOpResolver);
                }
        };
    }
}

#endif // NOOPRESOLVER_HPP
