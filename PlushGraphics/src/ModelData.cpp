#include "ModelData.hpp"
#include "ModelDataSpec.hpp"
#include "ModelVertex.hpp"

namespace PlushGraphics {
    ModelData::ModelData(ModelDataSpec spec):
    identifier(spec.getModelDataFileName()){
        // add vertex reading code
    }
}