#ifndef DRAWMod_HPP
#define DRAWMod_HPP

#include "Drawable/ManagedDrawable.hpp"
#include "ModelInstance/ManagedModelInstance.hpp"
#include "PlushEngine.hpp"
#include "EntityMod.hpp"

namespace PlushEngine {
    namespace EntityMods {
        class DrawMod : public EntityMod{
            public:
                static SharedPtrEntityMod constructAsEntityMod(ManagedEntity entity, PlushGraphics::ManagedModelInstance modelInstance);
                
                DrawMod(ManagedEntity _owningEntity, PlushGraphics::ManagedModelInstance modelInstance);

            private:
                static PlushGraphics::ManagedDrawable createNeededDrawable(ManagedEntity entity, PlushGraphics::ManagedModelInstance modelInstance);

                PlushGraphics::ManagedDrawable linkedDrawable;
        };
    }
}

#endif // DRAWMod_HPP
