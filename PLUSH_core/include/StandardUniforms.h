#include "ShaderUniforms.h"

namespace PLUSH {
    enum StandardUniformCode{
        NONSTANDARD_UNIFORM = 0,
        WINDOW_ASPECT_RATIO,
        LAYER_POSITION,
        LAYER_OFFSET,
        LAYER_HALF_DIMENSIONS,
        LAYER_DIMENSIONS,
        ENTITY_POSITION_2D,
        ENTITY_POSITION_2D_X,
        ENTITY_POSITION_2D_Y,
        ENTITY_SCALE_2D,
        ENTITY_SCALE_2D_X,
        ENTITY_SCALE_2D_Y,
        ENTITY_PRIMARY_TEXTURE
    };

    inline StandardUniformCode getStandardUniformCode(OPENGL_management::ShaderUniformTarget target){
        if(target.name == "aspectRatio" && target.type == OPENGL_management::OPENGL_FLOAT){
            return WINDOW_ASPECT_RATIO;
        }

        else if (
            target.name == "layerPosition" && target.type == OPENGL_management::OPENGL_FLOAT_VEC_2
        ){
            return LAYER_POSITION;
        }

        else if (
            target.name == "layerOffset" && target.type == OPENGL_management::OPENGL_FLOAT_VEC_2
        ){
            return LAYER_OFFSET;
        }

        else if (
            target.name == "layerHalfDimensions" && target.type == OPENGL_management::OPENGL_FLOAT_VEC_2
        ){
            return LAYER_HALF_DIMENSIONS;
        }

        else if (
            target.name == "primaryTexture" && target.type == OPENGL_management::OPENGL_SAMPLER2D
        ){
            return ENTITY_PRIMARY_TEXTURE;
        }

        else if (
            target.name == "EntityX" && target.type == OPENGL_management::OPENGL_FLOAT
        ){
            return ENTITY_POSITION_2D_X;
        }

        else if (
            target.name == "EntityY" && target.type == OPENGL_management::OPENGL_FLOAT
        ){
            return ENTITY_POSITION_2D_Y;
        }

        else if (
            target.name == "EntityScaleX" && target.type == OPENGL_management::OPENGL_FLOAT
        ){
            return ENTITY_SCALE_2D_X;
        }

        else if (
            target.name == "EntityScaleY" && target.type == OPENGL_management::OPENGL_FLOAT
        ){
            return ENTITY_SCALE_2D_Y;
        }

        return NONSTANDARD_UNIFORM;
    }
}