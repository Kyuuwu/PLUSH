#ifndef MANAGEDENTITY_HPP
#define MANAGEDENTITY_HPP

#include "PlushEngine.hpp"
#include "ManagedObject.hpp"
#include "Entity.hpp"
#include "Shader/ManagedShader.hpp"

namespace PlushEngine {
    class ManagedEntity : public PlushUtil::ManagedObject<Entity>{
        public:
            friend class EntityMod;

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

            void addOperator(SharedPtrEntityMod op){
                (*this)->_addOperator(op);
            }

            void runLogicUpdateOnAllOperators() {
                (*this)->_runLogicUpdateOnAllOperators();
            }

            void runPredrawTasksOnAllOperators(){
                (*this)->_runPredrawTasksOnAllOperators();
            }

            void resolveUniformRequirementsWithAllOperators(PlushGraphics::ManagedShader shader){
                (*this)->_resolveUniformRequirementsWithAllOperators(shader);
            }

            EntityIdentifier getIdentifier() const{
                return (*this)->getIdentifier();
            }
    };
}

#endif // MANAGEDENTITY_HPP
