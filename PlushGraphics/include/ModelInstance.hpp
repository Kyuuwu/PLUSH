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

            void draw();

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
            size_t numVertices;
    };
}

#endif // MODELINSTANCE_HPP
