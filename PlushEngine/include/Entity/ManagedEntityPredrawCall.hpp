#ifndef MANAGEDENTITYPREDRAWCALL_HPP
#define MANAGEDENTITYPREDRAWCALL_HPP

#include "Callable.hpp"
#include "Entity/ManagedEntity.hpp"

namespace PlushEngine {
    class ManagedEntityPredrawCall : public PlushUtil::Callable{
        public:
            ManagedEntityPredrawCall(ManagedEntity _entity):
                entity(_entity){}

            virtual void call() override{
                entity.runPredrawTasksOnAllMods();
            }

        private:
            ManagedEntity entity;
    };
}

#endif // MANAGEDENTITYPREDRAWCALL_HPP
