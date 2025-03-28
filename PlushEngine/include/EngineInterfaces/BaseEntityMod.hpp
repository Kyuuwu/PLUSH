#ifndef BASEENTITYMOD_HPP
#define BASEENTITYMOD_HPP

#include "PlushEngine.hpp"
#include "PlushGraphics.hpp"
#include "Shader/ManagedShader.hpp"
#include "../Entity/ManagedEntity.hpp"

namespace PlushEngine {
    namespace EngineInterfaces{
        class BaseEntityMod{ 
            // should this inherit from UniformResolver? it has very similar features, with some additional ones, 
            // but it is icky to let it intermesh under UniformResolver pointers
            // and it becomes double depth inheritance.
            // Plus, one inherited function should in all likelihood be left unused
            public:
                BaseEntityMod() = delete;
                virtual ~BaseEntityMod() {}

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

            protected:
                BaseEntityMod(ManagedEntity _owningEntity):
                    owningEntity(_owningEntity){}
                // prevents instantiation of base class

                // std::vector<SharedPtrEntityOperator> getOperatorSharedPtrsFromEntity(ManagedEntity entity);
                ManagedEntity owningEntity;

        };
    }
}

#endif // BASEENTITYMOD_HPP
