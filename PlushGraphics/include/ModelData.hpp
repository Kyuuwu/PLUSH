#ifndef MODELDATA_HPP
#define MODELDATA_HPP

#include "ModelVertex.hpp"
#include "PlushGraphics.hpp"
#include "ModelDataIdentifier.hpp" 
#include "ShaderInputSlotIdentifier.hpp"
#include <vector>

namespace PlushGraphics {
    class ModelData{
        public:
            using Spec = ModelDataSpec;
            using Identifier = ModelDataIdentifier;

            ModelData(ModelDataSpec spec);
            ~ModelData(); 

            ModelData(const ModelData&) = delete;
            ModelData& operator=(const ModelData&) = delete;
            ModelData(ModelData&&) = delete;
            ModelData& operator=(ModelData&&) = delete;

            ModelDataIdentifier getIdentifier() const { return identifier; }

            std::vector<ShaderMetadata::ShaderInputSlotIdentifier> getTargetedInputSlots() const { return targetedInputSlots; }

            std::vector<ModelVertex> getVertices() const { return vertices; }

            std::vector<size_t> getIndices() const { return indices; }


        private:
            ModelDataIdentifier identifier;

            std::vector<ShaderMetadata::ShaderInputSlotIdentifier> targetedInputSlots;
            std::vector<ModelVertex> vertices;
            std::vector<size_t> indices;
    };
}

#endif // MODELDATA_HPP
