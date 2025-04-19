#include "PlushEngine.hpp"
#include "PlushGraphics.hpp"
#include "UniformResolver.hpp"
#include "Entity/ManagedEntity.hpp"

namespace PlushEngine {
    namespace EngineUniformResolvers {
        class EntityUniformResolver : public PlushGraphics::UniformResolver{
            public:
                EntityUniformResolver(ManagedEntity _entity):
                    entity(_entity){}

                EntityUniformResolver(const EntityUniformResolver& other):
                    entity(other.entity) {}

                PlushGraphics::UniquePtrUniformResolver duplicateSelf() const override{
                    return PlushGraphics::UniquePtrUniformResolver(new EntityUniformResolver(*this));
                }

                void resolveUniformRequirements(PlushGraphics::ManagedShader shader) override{
                    entity.resolveUniformRequirementsWithAllMods(shader);
                }

            private:
                ManagedEntity entity;
        };
    }
}