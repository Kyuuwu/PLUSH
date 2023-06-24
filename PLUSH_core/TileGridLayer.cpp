#include "PLUSH_core_includes.h"
#include "OPENGL_management_includes.h"
#include "Helpers.h"

#include <iostream>

namespace PLUSH {
    TileGridLayer::TileGridLayer(std::string name):
    DrawableLayer(name)
    {
        tilegridshader = OPENGL_management::ShaderLibrary::getShaderByName("TileShader");
        moveableshader = OPENGL_management::ShaderLibrary::getShaderByName("MoveableTileShader");
    }

    void TileGridLayer::draw(std::vector<OPENGL_management::ShaderUniform> external_uniforms){
        if(!uniforms_up_to_date){
            generateUniforms();
        }

        external_uniforms.insert(external_uniforms.begin(), uniforms.begin(), uniforms.end());

        unsigned int min_i = (unsigned int)(offset[0]/tileDimensions[0]);

        unsigned int max_i = (unsigned int)((offset[0] + dimensions[0])/tileDimensions[0])+1;

        unsigned int min_j = (unsigned int)(offset[1]/tileDimensions[1]);

        unsigned int max_j = (unsigned int)((offset[1] + dimensions[1])/tileDimensions[1])+1;

        tilegrid->draw(tilegridshader.get(), external_uniforms, min_i, max_i, min_j, max_j);

        for(CoordPair coords: highlights){
            tilegrid->drawHighlight(tilegridshader.get(), external_uniforms, coords.i, coords.j);
        }

        for(std::shared_ptr<Entity> moveable : moveables){
            moveable->drawWithShader(moveableshader.get(), external_uniforms);
        }
    }

    void TileGridLayer::setTileGrid(std::shared_ptr<TileGrid> newTileGrid){
        tilegrid = newTileGrid;
    }

    void TileGridLayer::generateUniforms(){
        OPENGL_management::ShaderUniform dimensions_uniform, position_uniform, offset_uniform, tileDimensions_uniform;

        dimensions_uniform.target.name = "tileGridDimensions";
        dimensions_uniform.target.type = OPENGL_management::OPENGL_FLOAT_VEC_2;
        dimensions_uniform.value.fptr = &dimensions[0];
        
        position_uniform.target.name = "tileGridPosition";
        position_uniform.target.type = OPENGL_management::OPENGL_FLOAT_VEC_2;
        position_uniform.value.fptr = &position[0];

        offset_uniform.target.name = "tileGridOffset";
        offset_uniform.target.type = OPENGL_management::OPENGL_FLOAT_VEC_2;
        offset_uniform.value.fptr = &offset[0];

        tileDimensions_uniform.target.name = "tileDimensions";
        tileDimensions_uniform.target.type = OPENGL_management::OPENGL_FLOAT_VEC_2;
        tileDimensions_uniform.value.fptr = &tileDimensions[0];

        std::vector<OPENGL_management::ShaderUniform> newUniformList;
        newUniformList.push_back(dimensions_uniform);
        newUniformList.push_back(position_uniform);
        newUniformList.push_back(offset_uniform);
        newUniformList.push_back(tileDimensions_uniform);
        
        uniforms = newUniformList;
        uniforms_up_to_date = true;
    }

    void TileGridLayer::snapToEdges_IfOutOfBounds(){

        if (offset[0] < 0.0){
            offset[0] = 0.0;
        }
        if (offset[1] < 0.0){
            offset[1] = 0.0;
        }
        if (offset[0] > tilegrid->getWidth()*tileDimensions[0] - dimensions[0]){
            offset[0] = tilegrid->getWidth()*tileDimensions[0] - dimensions[0];
        }
        if (offset[1] > tilegrid->getHeight()*tileDimensions[1] - dimensions[1]){
            offset[1] = tilegrid->getHeight()*tileDimensions[1] - dimensions[1];
        }

        if(dimensions[0] > tileDimensions[0]*tilegrid->getWidth()){
            offset[0] = 0.0;
        }   
        if(dimensions[1] > tileDimensions[1]*tilegrid->getHeight()){
            offset[1] = 0.0;
        }   
    }

    void TileGridLayer::incrementOffset(float x, float y){
        offset[0] = offset[0] + x;
        offset[1] = offset[1] + y;
    }

    void TileGridLayer::setOffset(float x, float y){
        offset[0] = x;
        offset[1] = y;
    }

    void TileGridLayer::setDimensions(float x, float y){
        dimensions[0] = x;
        dimensions[1] = y;
    }

    void TileGridLayer::setTileDimensions(float x, float y){
        tileDimensions[0] = x;
        tileDimensions[1] = y;
    }

    void TileGridLayer::setPosition(float x, float y){
        position[0] = x;
        position[1] = y;
    }

    void TileGridLayer::addMoveable(std::shared_ptr<Entity> moveable){
        moveables.push_back(moveable);
    }

    std::vector<std::shared_ptr<Entity>> TileGridLayer::getMoveables(){
        return moveables;
    }

    void TileGridLayer::setMoveablePosition(std::string moveableName, glm::vec2 position){
        OPENGL_management::ShaderUniform posX, posY;
        posX.target.name = "posX";
        posX.target.type = OPENGL_management::OPENGL_FLOAT;
        posX.value.f = position[0];

        posY.target.name = "posY";
        posY.target.type = OPENGL_management::OPENGL_FLOAT;
        posY.value.f = position[1];

        std::vector<OPENGL_management::ShaderUniform> positionuniforms;

        positionuniforms.push_back(posX);
        positionuniforms.push_back(posY);

        for(std::shared_ptr<Entity> moveable : moveables){
            if(moveable->getName() == moveableName){
                moveable->setInternalUniforms(positionuniforms);
            }
        }
    }

    void TileGridLayer::setMoveablePosition(std::string moveableName, float x, float y){
        setMoveablePosition(moveableName, glm::vec2(x, y));
    }

    void TileGridLayer::setHighlights(std::vector<CoordPair> newhighlights){
        highlights = newhighlights;
    }

    void TileGridLayer::resetHighlights(){
        setHighlights(std::vector<CoordPair>());
    }

    void TileGridLayer::addHighlight(unsigned int i, unsigned int j){
        CoordPair pair;
        pair.i = i;
        pair.j = j;
        highlights.push_back(pair);
    }

    float TileGridLayer::getOffsetX(){
        return offset[0];
    }
    float TileGridLayer::getOffsetY(){
        return offset[1];
    }
}