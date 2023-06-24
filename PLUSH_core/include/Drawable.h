#ifndef PLUSH_DRAWABLE_LAYER
#define PLUSH_DRAWABLE_LAYER

#include <vector>
#include "ShaderUniforms.h"

namespace PLUSH {
    class DrawableLayer{
        public:
            DrawableLayer(std::string name = "Default_layer_name:FIX_THIS");

            virtual void draw(std::vector<OPENGL_management::ShaderUniform> external_uniforms = std::vector<OPENGL_management::ShaderUniform>()) = 0;
            void setName(std::string newname);
            std::string getName();
        
        protected:
            std::string name;
    };
}

#endif