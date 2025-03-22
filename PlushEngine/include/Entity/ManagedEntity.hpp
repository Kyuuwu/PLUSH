#ifndef MANAGEDENTITY_HPP
#define MANAGEDENTITY_HPP

#include "ManagedObject.hpp"
#include "Entity.hpp"

namespace PlushEngine {
    class ManagedEntity : public PlushUtil::ManagedObject<Entity>{
        public:
            ManagedEntity(ManagedEntity&& other) noexcept:
                PlushUtil::ManagedObject<Entity>(std::move(other))
            {}

            ManagedEntity(const ManagedEntity& other):
                PlushUtil::ManagedObject<Entity>(other)
            {}

            template <typename T>
            ManagedEntity(T&& arg):
                PlushUtil::ManagedObject<Entity>(std::forward<T>(arg)){}

            template <typename T>
            ManagedEntity& operator=(T&& arg){
                PlushUtil::ManagedObject<Entity>::operator=(std::forward<T>(arg));
                return *this;
            }

            using Object = Entity;

            void runLogicUpdate() {
                (*this)->_runLogicUpdate();
            }

            void getIdentifier() const{
                (*this)->getIdentifier();
            }
    };
}

#endif // MANAGEDENTITY_HPP
