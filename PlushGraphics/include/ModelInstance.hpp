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

            void draw(){
                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
                // glBindVertexArray(0);
            }

        private:
            ModelInstanceIdentifier identifier;
            bufferReferenceID VAO;
            bufferReferenceID VBO;
            bufferReferenceID EBO;
            size_t numIndices;
    };
}

#endif // MODELINSTANCE_HPP
