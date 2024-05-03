#include "PLUSH_core_includes.h"
#include "OPENGL_management_includes.h"
#include "Exceptions.h"
#include "Helpers.h"

#include <iostream>

namespace PLUSH {
    TileGrid::TileGrid(std::shared_ptr<Instance> entity, unsigned int width, unsigned int height){
        initializeGrid(entity, width, height);
    }

    TileGrid::TileGrid(unsigned int width, unsigned int height){
        std::shared_ptr<Instance> defaulttile(new Instance("Tile", OPENGL_management::ModelLibrary::getModelByName("tile.vx")));
        defaulttile->getStatusPointer()->visible=true;
        initializeGrid(defaulttile, width, height);
    }

    void TileGrid::initializeGrid(std::shared_ptr<Instance> entity, unsigned int width, unsigned int height){
        this->width = width;
        this->height = height;

        for(uint i = 0; i < width; i ++){
            for(uint j = 0; j < height; j++){
                // tiles.push_back(entity);
                tiles.push_back(entity->copy());
            }
        }

        std::shared_ptr<Instance> newhighlighter(new Instance("Highlighter", "tile.vx"));
        newhighlighter->getStatusPointer()->visible = true;
        newhighlighter->setTexture2DUniform("primaryTexture", "HighlighterThick");

        highlighter = newhighlighter;
    }

    void TileGrid::draw(OPENGL_management::Shader* shader, std::vector<OPENGL_management::ShaderUniform> external_uniforms){
        draw(shader, external_uniforms, 0, width, 0, height);
    }

    void TileGrid::draw(OPENGL_management::Shader* shader, std::vector<OPENGL_management::ShaderUniform> external_uniforms, unsigned int min_i, unsigned int max_i, unsigned int min_j, unsigned int max_j){

        // if(min_i < 0){
        //     min_i = 0;
        // }
        if(max_i > width){
            max_i = width;
        }
        // if(min_j < 0){
        //     min_j = 0;
        // }
        if(max_j > height){
            max_j = height;
        }

        // std::cout << "Drawing tilegrid" << std::endl;

        shader->resetAllUniformSetChecks();

        for (OPENGL_management::ShaderUniform uniform: external_uniforms){
            shader->setUniform(uniform.value, uniform.target);
        }

        // std::cout << "Setting tilegrid uniforms time: ";
        // PLUSH_helpers::outputTimeElapsed();
        // std::cout << std::endl;

        // std::cout << "Set external uniforms" << std::endl;

        std::vector<OPENGL_management::ShaderUniform> tileUniforms;
        OPENGL_management::ShaderUniform tileIndexXUniform, tileIndexYUniform;
        tileIndexXUniform.target.name = "tileIndexX";
        tileIndexXUniform.target.type = OPENGL_management::OPENGL_UINT;
        tileIndexYUniform.target.name = "tileIndexY";
        tileIndexYUniform.target.type = OPENGL_management::OPENGL_UINT;

        tileUniforms.push_back(tileIndexXUniform);
        tileUniforms.push_back(tileIndexYUniform);

        shader->use();
        shader->setBeingUsed(true);

        for(unsigned int i = min_i; i < max_i; i++){
            for(unsigned int j = min_j; j < max_j; j++){
                tileUniforms[0].value.u = i;
                tileUniforms[1].value.u = j;

                getTile(i,j)->drawWithShader(shader, tileUniforms, false);

            }
        }
        shader->setBeingUsed(false);


        // std::cout << "Drawing tiles time: ";
        // PLUSH_helpers::outputTimeElapsed();
        // std::cout << std::endl;
    }

    void TileGrid::drawHighlight(OPENGL_management::Shader* shader, std::vector<OPENGL_management::ShaderUniform> external_uniforms, unsigned int i, unsigned int j){
        // shader->resetUniformSetChecks();

        // std::cout << "Drawing highlight at " << i << " " << j << std::endl;

        for (OPENGL_management::ShaderUniform uniform: external_uniforms){
            shader->setUniform(uniform.value, uniform.target);
        }

        std::vector<OPENGL_management::ShaderUniform> tileUniforms;
        OPENGL_management::ShaderUniform tileIndexXUniform, tileIndexYUniform;
        tileIndexXUniform.target.name = "tileIndexX";
        tileIndexXUniform.target.type = OPENGL_management::OPENGL_UINT;
        tileIndexXUniform.value.u = i;

        tileIndexYUniform.target.name = "tileIndexY";
        tileIndexYUniform.target.type = OPENGL_management::OPENGL_UINT;
        tileIndexYUniform.value.u = j;

        tileUniforms.push_back(tileIndexXUniform);
        tileUniforms.push_back(tileIndexYUniform);

        tileUniforms.insert(tileUniforms.begin(), external_uniforms.begin(), external_uniforms.end());

        highlighter->drawWithShader(shader, tileUniforms, true);


    }

    std::shared_ptr<Instance> TileGrid::getTile(unsigned int i, unsigned int j){
        if (i >= width || j >= height){
            throw(PLUSH_helpers::OUT_OF_RANGE);
        }

        return tiles.at(i*height + j);
    }

    unsigned int TileGrid::getHeight(){
        return height;
    }

    unsigned int TileGrid::getWidth(){
        return width;
    }
}