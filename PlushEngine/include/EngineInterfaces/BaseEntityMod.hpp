#ifndef BASEENTITYMOD_HPP
#define BASEENTITYMOD_HPP

#include "PlushEngine.hpp"
#include "PlushGraphics.hpp"
#include "Shader/ManagedShader.hpp"
#include "../Entity/ManagedEntity.hpp"
#include <optional>

namespace PlushEngine {
    namespace EngineInterfaces{
        class BaseEntityMod{ 
            // should this inherit from UniformResolver? it has very similar features, with some additional ones, 
            // but it is icky to let it intermesh under UniformResolver pointers
            // and it becomes double depth inheritance.
            // Plus, one inherited function should in all likelihood be left unused
            public:
                virtual ~BaseEntityMod() {}
                // BaseEntityMod(const BaseEntityMod&) = delete;
                // BaseEntityMod& operator=(const BaseEntityMod&) = delete;
                // BaseEntityMod& operator=(BaseEntityMod&&) = delete;

                // defaults of all interface methods are no-ops, must be overriden

                /// runs directly before draw, single-threaded, context-specific, uniforms
                virtual void resolveUniformRequirements(PlushGraphics::ManagedShader shader){
                    #pragma unused(shader)
                } 

                /// runs at some point before graphics update, ideally multi-threadable, not-context-specific, operator/entity-internal
                virtual void runPredrawTasks() {}

                virtual void runLogicUpdate() {} 

                // Shouldn't be necessary, since these should be directly instantiable with full function, and are specific to a specific Entity 
                // virtual UniquePtrEntityOperator duplicateSelf() const = 0; 

                virtual void setOwningEntity(ManagedEntity _ent){
                    owningEntity = _ent;
                    processNewOwningEntity();
                }

            protected:
                BaseEntityMod() {}

                BaseEntityMod(ManagedEntity _owningEntity): // perhaps obsolete
                    owningEntity(_owningEntity){
                        processNewOwningEntity();
                    }
                    
                virtual void processNewOwningEntity(){}

                // std::vector<SharedPtrEntityOperator> getOperatorSharedPtrsFromEntity(ManagedEntity entity);
                std::optional<ManagedEntity> owningEntity;

        };
    }
}

#endif // BASEENTITYMOD_HPP
