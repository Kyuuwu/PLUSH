#ifndef SHADER_HPP
#define SHADER_HPP

#include "PlushGraphics.hpp"
#include "ShaderIdentifier.hpp"
#include "ShaderInputSlot.hpp"
#include "ShaderUniformSlotFulfillmentState.hpp"
#include "ShaderSpec.hpp"
#include <vector>
#include <map>
#include <string>

namespace PlushGraphics {
    class Shader{
        public:
            using Identifier = ShaderIdentifier;
            using Spec = ShaderSpec;
            
            Shader(ShaderSpec spec);
            ~Shader(); // Shader can only be created and destroyed, all other functionality must be handled on the level of ManagedShader.

            Shader(const Shader&) = delete; // explicitly forbid copy
            Shader& operator=(const Shader&) = delete; // explicitly forbid copy assign
            Shader(Shader&&) = delete; //explicitly forbid move
            Shader& operator=(Shader&&) = delete; //explicitly forbid move assign

            void useShader();

            void setUniform(ShaderMetadata::ShaderUniformPayload value);

            std::vector<ShaderMetadata::ShaderUniformSlotIdentifier> getUniformSlotIdentifiers() const;
            std::vector<ShaderMetadata::ShaderInputSlotIdentifier> getInputSlotIdentifiers() const;
            std::vector<ShaderMetadata::ShaderInputSlot> getInputSlots() const {return inputSlots;}

            ShaderIdentifier getIdentifier() const { return identifier; }

        private:

            ShaderIdentifier identifier;

            ShaderMetadata::ShaderUniformSlot& getUniformSlot(ShaderMetadata::ShaderUniformSlotIdentifier identifier);
            shaderSlotLocation_t getUniformSlotLocation(ShaderMetadata::ShaderUniformSlotIdentifier identifier);

            void checkCompileErrors(unsigned int shader, std::string type);

            shaderObjectReferenceID shaderProgramID;

            std::vector<ShaderMetadata::ShaderUniformSlotIdentifier> uniformSlotIdentifiers;
            std::vector<ShaderMetadata::ShaderUniformSlot> uniformSlots;
            std::map<ShaderMetadata::ShaderUniformSlotIdentifier, size_t> uniformSlotIndexMap;

            std::vector<ShaderMetadata::ShaderInputSlot> inputSlots;
    };
}

#endif // SHADER_HPP
