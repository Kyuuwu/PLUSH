

#include "EngineInterfaces/BaseEntityMod.hpp"
#include "Entity/ManagedEntity.hpp"
#include "PlushGraphics.hpp"
#include "UniformResolver.hpp"

namespace PlushEngine {
    namespace EntityMods {
        class ResolverMod : public EngineInterfaces::BaseEntityMod{
            public:
                template<PlushGraphics::UniResDerived T>
                ResolverMod(ManagedEntity owningEntity, T&& ur):
                    EngineInterfaces::BaseEntityMod(owningEntity),
                    resolver(new T(std::move(ur))) {}

                template<PlushGraphics::UniResDerived T>
                ResolverMod(ManagedEntity owningEntity, const T& ur):
                    EngineInterfaces::BaseEntityMod(owningEntity),
                    resolver(new T(ur)) {}

                void resolveUniformRequirements(PlushGraphics::ManagedShader shader) override {
                    resolver.get()->resolveUniformRequirements(shader);
                }

            private:
                PlushGraphics::SharedPtrUniformResolver resolver;
        };
    }
}