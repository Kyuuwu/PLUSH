#ifndef MANAGEDMODELDATA_HPP
#define MANAGEDMODELDATA_HPP

#include "ModelData.hpp"
#include "ManagedObject.hpp"
#include "ModelDataSpec.hpp"

namespace PlushGraphics {
    class ManagedModelData : public PlushUtil::ManagedObject<ModelData>{
        public:

            ManagedModelData(ManagedModelData&& other) noexcept:
                PlushUtil::ManagedObject<ModelData>(std::move(other))
            {}

            ManagedModelData(const ManagedModelData& other):
                PlushUtil::ManagedObject<ModelData>(other)
            {}

            template <typename T>
            ManagedModelData(T&& arg):
                PlushUtil::ManagedObject<ModelData>(std::forward<T>(arg)){}

            template <typename T>
            ManagedModelData& operator=(T&& arg){
                PlushUtil::ManagedObject<ModelData>::operator=(std::forward<T>(arg));
                return *this;
            }

            using Object = ModelData;


            std::vector<ShaderMetadata::ShaderInputSlotIdentifier> getTargetedInputSlots() const { 
                return operator->()->_getTargetedInputSlots(); // protected -> operator 
            }

            std::vector<ModelVertex> getVertices() const { 
                return operator->()->_getVertices(); 
            }

            std::vector<size_t> getIndices() const { 
                return operator->()->_getIndices(); 
            }
        
        private:
    };
}

#endif // MANAGEDMODELDATA_HPP
