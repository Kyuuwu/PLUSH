#ifndef MANAGEDMODELINSTANCE_HPP
#define MANAGEDMODELINSTANCE_HPP

#include "ManagedObject.hpp"
#include "ModelInstance.hpp"

namespace PlushGraphics {
    class ManagedModelInstance : public PlushUtil::ManagedObject<ModelInstance>{
        public:

            ManagedModelInstance(ManagedModelInstance&& other) noexcept:
                PlushUtil::ManagedObject<ModelInstance>(std::move(other))
            {}

            ManagedModelInstance(const ManagedModelInstance& other):
                PlushUtil::ManagedObject<ModelInstance>(other)
            {}

            template <typename T>
                ManagedModelInstance(T&& arg):
                    PlushUtil::ManagedObject<ModelInstance>(std::forward<T>(arg)){}

            template <typename T>
            ManagedModelInstance& operator=(T&& arg){
                return PlushUtil::ManagedObject<ModelInstance>::operator=(std::forward<T>(arg));
            }

            using Object = ModelInstance;

            void drawModel() const{
                (*this)->draw();
            }
    };
}

#endif // MANAGEDMODELINSTANCE_HPP
