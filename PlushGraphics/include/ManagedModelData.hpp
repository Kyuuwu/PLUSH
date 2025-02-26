#ifndef MANAGEDMODELDATA_HPP
#define MANAGEDMODELDATA_HPP

#include "ModelData.hpp"
#include "ManagedObject.hpp"
#include "ModelDataSpec.hpp"

namespace PlushGraphics {
    class ManagedModelData : public PlushUtil::ManagedObject<ModelData>{
        public:
            template <typename T>
            ManagedModelData(T&& arg):
                PlushUtil::ManagedObject<ModelData>(std::forward<T>(arg)){}

            template <typename T>
            ManagedModelData& operator=(T&& arg){
                return PlushUtil::ManagedObject<ModelData>::operator=(std::forward<T>(arg));
            }

            using Object = ModelData;
        
        private:
    };
}

#endif // MANAGEDMODELDATA_HPP
