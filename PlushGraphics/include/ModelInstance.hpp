#ifndef MODELINSTANCE_HPP
#define MODELINSTANCE_HPP

#include "PlushGraphics.hpp"
#include "ModelInstanceIdentifier.hpp"
#include "PlushGraphicsOpenGL.hpp"

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

            void draw(){
                if(VAO_map.count(OpenGL::getActiveWindowIdentifier()) == 0){
                    setUpNewVAO();
                }

                glBindVertexArray(VAO_map[OpenGL::getActiveWindowIdentifier()]);
                glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
                // glBindVertexArray(0);
            }

        private:
            void setUpNewVAO();

            ManagedModelData modelData;
            ManagedShader shader;

            void loadVertexDataIntoBuffersAndSetupVertexAttributes(bool loadVertexData, std::vector<ModelVertex> vertices = std::vector<ModelVertex>());

            ModelInstanceIdentifier identifier;
            
            std::map<WindowIdentifier, bufferReferenceID> VAO_map;
            bufferReferenceID VBO;
            bufferReferenceID EBO;
            size_t numIndices;
    };
}

#endif // MODELINSTANCE_HPP
