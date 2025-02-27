#ifndef MODELINSTANCE_HPP
#define MODELINSTANCE_HPP

#include "PlushGraphics.hpp"
#include "ModelInstanceIdentifier.hpp"

namespace PlushGraphics {
    class ModelInstance{
        public:
            using Spec = ModelInstanceSpec;
            using Identifier = ModelInstanceIdentifier;

            ModelInstance(ModelInstanceSpec spec);
            ~ModelInstance();

            ModelInstance(const ModelInstance&) = delete;
            ModelInstance& operator=(const ModelInstance&) = delete;
            ModelInstance(ModelInstance&&) = delete;
            ModelInstance& operator=(ModelInstance&&) = delete;

            ModelInstanceIdentifier getIdentifier() const { return identifier; }

        private:
            ModelInstanceIdentifier identifier;
    };
}

#endif // MODELINSTANCE_HPP
