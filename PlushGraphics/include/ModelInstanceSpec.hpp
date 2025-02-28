#ifndef MODELINSTANCESPEC_HPP
#define MODELINSTANCESPEC_HPP

#include "ManagedModelData.hpp"
#include "ManagedShader.hpp"

namespace PlushGraphics {
    class ModelInstanceSpec{
        public:
            ModelInstanceSpec(ManagedModelData _modelData, ManagedShader _shader)
            : modelData(_modelData), shader(_shader) {}

            ManagedModelData getModelData() const { return modelData; }
            ManagedShader getShader() const { return shader; }

        private:
            ManagedModelData modelData;
            ManagedShader shader;
    };
}

#endif // MODELINSTANCESPEC_HPP
