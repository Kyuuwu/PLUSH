#ifndef MANAGEDSHADER_HPP
#define MANAGEDSHADER_HPP

#include "PlushGraphics.hpp"
#include "ManagedObject.hpp"
#include "ShaderUniformSlotIdentifier.hpp"
#include "ShaderInputSlotIdentifier.hpp"
#include "ShaderUniformPayload.hpp"
#include "ShaderInputSlot.hpp"
#include "Shader.hpp"

namespace PlushGraphics {
    class ManagedShader : public PlushUtil::ManagedObject<Shader>{
        public:

            ManagedShader(ManagedShader&& other) noexcept:
                PlushUtil::ManagedObject<Shader>(std::move(other))
            {}

            ManagedShader(const ManagedShader& other):
                PlushUtil::ManagedObject<Shader>(other)
            {}

            template <typename T>
            ManagedShader(T&& arg):
                PlushUtil::ManagedObject<Shader>(std::forward<T>(arg)){}

            template <typename T>
            ManagedShader& operator=(T&& arg){
                PlushUtil::ManagedObject<Shader>::operator=(std::forward<T>(arg));
                return *this;
            }

            using Object = Shader;

            void useShader() const{
                (*this)->_useShader();
            }

            void acceptUniformResolver(WeakPtrUniformResolver resolver);

            std::vector<ShaderMetadata::ShaderUniformSlotIdentifier> getUniformSlotIdentifiers() const{
                return (*this)->_getUniformSlotIdentifiers(); // use protected -> operator to get from Shader
            }
            std::vector<ShaderMetadata::ShaderInputSlotIdentifier> getInputSlotIdentifiers() const{
                return (*this)->_getInputSlotIdentifiers(); // use protected -> operator to get from Shader
            }
            std::vector<ShaderMetadata::ShaderInputSlot> getInputSlots() const{
                return operator->()->_getInputSlots(); // use protected -> operator to get from Shader
            }

            // void setUniform(ShaderMetadata::ShaderUniformPayload value){
            //     operator->()->setUniform(value); // use protected -> operator
            // } 

            bool tryToSetUniform(ShaderMetadata::ShaderUniformPayload value){
                return (*this)->_tryToSetUniform(value);
            }


            void setUniformNew(ShaderMetadata::ShaderUniformPayload payload){
                (*this)->_setUniformNew(payload);
            }

            void clearDrawableLevelUniforms(){
                (*this)->_clearDrawableLevelUniforms();
            }

            void clearLayerLevelUniforms(){
                (*this)->_clearLayerLevelUniforms();
            }

            void clearWindowLevelUniforms(){
                (*this)->_clearWindowLevelUniforms();
            }

            void prepareForWindowUniforms(){
                (*this)->_prepareForWindowUniforms();
            }

            void prepareForLayerUniforms(){
                (*this)->_prepareForLayerUniforms();
            }

            void prepareForDrawableUniforms(){
                (*this)->_prepareForDrawableUniforms();
            }

            void prepareForDraw(){
                (*this)->_prepareForDraw();
            }

            //for sorting purposes ONLY
            bool operator<(const ManagedShader& other) const{
                return getIdentifier() < other.getIdentifier();
            }
        
        private:
    };
}

#endif // MANAGEDSHADER_HPP
