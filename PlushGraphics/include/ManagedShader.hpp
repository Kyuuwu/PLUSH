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
                return PlushUtil::ManagedObject<Shader>::operator=(std::forward<T>(arg));
            }

            using Object = Shader;

            void useShader() const{
                (*this)->useShader();
            }

            std::vector<ShaderMetadata::ShaderUniformSlotIdentifier> getUniformSlotIdentifiers() const{
                return (*this)->getUniformSlotIdentifiers(); // use protected -> operator to get from Shader
            }
            std::vector<ShaderMetadata::ShaderInputSlotIdentifier> getInputSlotIdentifiers() const{
                return (*this)->getInputSlotIdentifiers(); // use protected -> operator to get from Shader
            }
            std::vector<ShaderMetadata::ShaderInputSlot> getInputSlots() const{
                return operator->()->getInputSlots(); // use protected -> operator to get from Shader
            }

            void setUniform(ShaderMetadata::ShaderUniformPayload value){
                operator->()->setUniform(value); // use protected -> operator
            } 
        
        private:
    };
}

#endif // MANAGEDSHADER_HPP
