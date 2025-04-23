#ifndef MANAGEDENTITY_HPP
#define MANAGEDENTITY_HPP

#include "PlushEngine.hpp"
#include "ManagedObject.hpp"
#include "Entity.hpp"
#include "Shader/ManagedShader.hpp"
#include <memory>
#include <vector>

namespace PlushEngine {
    class ManagedEntity : public PlushUtil::ManagedObject<Entity>{
        public:
            friend class EntityMod;

            ManagedEntity(); // create a fresh entity through the Global EntityRegistry

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

            ManagedEntity& addEntityMod(SharedPtrEntityMod mod);

            template <ModDerived M>
            ManagedEntity& addEntityMod(M&& mod){
                SharedPtrEntityMod moved_mod = std::make_shared<M>(std::move(mod));
                addEntityMod(moved_mod);
                return *this;
            }

            void runLogicUpdateOnAllMods() {
                (*this)->_runLogicUpdateOnAllMods();
            }

            void runPredrawTasksOnAllMods(){
                (*this)->_runPredrawTasksOnAllMods();
            }

            void resolveUniformRequirementsWithAllMods(PlushGraphics::ManagedShader shader){
                (*this)->_resolveUniformRequirementsWithAllMods(shader);
            }

            std::vector<SharedPtrEntityMod> getEntityMods(){
                return (*this)->_getEntityMods();
            }

            EntityIdentifier getIdentifier() const{
                return (*this)->getIdentifier();
            }

            EntityStatus& status(){
                return (*this)->_status();
            }
    };
}

#endif // MANAGEDENTITY_HPP
