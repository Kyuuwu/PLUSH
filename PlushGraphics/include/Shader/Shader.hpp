#ifndef SHADER_HPP
#define SHADER_HPP

#include "PlushGraphics.hpp"
#include "ShaderIdentifier.hpp"
#include "ShaderInputSlot.hpp"
#include "ShaderUniformSlotFulfillmentState.hpp"
#include "ShaderMemento.hpp"
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

            void _useShader(); 

            bool _tryToSetUniform(ShaderMetadata::ShaderUniformPayload value); // returns true if successful
            void _setUniform(ShaderMetadata::ShaderUniformPayload value); // throws exception if matching uniform slot does not exist

            void _setUniformNew(ShaderMetadata::ShaderUniformPayload payload){
                tryToSetMementoUniform(*activeMemento, payload);
            }

            std::vector<ShaderMetadata::ShaderUniformSlotIdentifier> _getUniformSlotIdentifiers() const;
            std::vector<ShaderMetadata::ShaderInputSlotIdentifier> _getInputSlotIdentifiers() const;
            std::vector<ShaderMetadata::ShaderInputSlot> _getInputSlots() const {return inputSlots;}

            ShaderIdentifier getIdentifier() const { return identifier; }

            void _clearDrawableLevelUniforms(){
                drawableLevelMemento = layerLevelMemento;
            }

            void _clearLayerLevelUniforms(){
                layerLevelMemento = windowLevelMemento;
                _clearDrawableLevelUniforms(); // in theory unneeded, but
            }

            void _clearWindowLevelUniforms(){
                windowLevelMemento = ShaderMemento();
                _clearLayerLevelUniforms(); // in theory unneeded, but
            }

            void _prepareForWindowUniforms(){
                activeMemento = &windowLevelMemento;
            }

            void _prepareForLayerUniforms(){
                activeMemento = &layerLevelMemento;
            }

            void _prepareForDrawableUniforms(){
                activeMemento = &drawableLevelMemento;
            }

            // void _setWindowUniform(ShaderMetadata::ShaderUniformPayload payload, bool overrideExisting = true){
            //     tryToSetMementoUniform(windowLevelMemento, payload, overrideExisting);
            // }

            // void _setLayerUniform(ShaderMetadata::ShaderUniformPayload payload, bool overrideExisting = true){
            //     tryToSetMementoUniform(layerLevelMemento, payload, overrideExisting);
            // }

            // void _setDrawableUniform(ShaderMetadata::ShaderUniformPayload payload, bool overrideExisting = true){
            //     tryToSetMementoUniform(drawableLevelMemento, payload, overrideExisting);
            // }

            void _prepareForDraw(){
                commitFromMemento(drawableLevelMemento);
            }

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

            // contract: all stored mementos must only contain uniforms matching the shader
            ShaderMemento windowLevelMemento;
            ShaderMemento layerLevelMemento;
            ShaderMemento drawableLevelMemento;

            ShaderMemento* activeMemento = &windowLevelMemento;

            void tryToSetMementoUniform(ShaderMemento& memento, ShaderMetadata::ShaderUniformPayload payload, bool overrideExisting = true){
                if (uniformSlotIndexMap.contains(payload.getTargetSlotIdentifier())){
                    memento.setUniform(payload, overrideExisting);
                }
            }

            void commitFromMemento(ShaderMemento& memento); 
            void commitUniform(ShaderMetadata::ShaderUniformPayload value);

            ShaderMemento lastCommitedMemento;
    };
}

#endif // SHADER_HPP
