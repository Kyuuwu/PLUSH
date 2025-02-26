#ifndef MODELDATA_HPP
#define MODELDATA_HPP

#include "PlushGraphics.hpp"
#include "ModelDataIdentifier.hpp" 
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

            ModelDataIdentifier getIdentifier();

        private:
            ModelDataIdentifier identifier;

            std::vector<ModelVertex> vertices;
    };
}

#endif // MODELDATA_HPP
