#include "../include/EntityMods/DrawMod.hpp"
#include "Drawable/ManagedDrawable.hpp"
#include "Entity/ManagedEntity.hpp"
#include "GlobalGraphicsState.hpp"
#include "ModelInstance/ModelInstance.hpp"

#include "PlushEngine.hpp"
#include "../include/EngineUniformResolvers/EntityUniformResolver.hpp"

namespace PlushEngine {
    SharedPtrEntityMod EntityMods::DrawMod::constructAsEntityMod(ManagedEntity entity, PlushGraphics::ManagedModelInstance modelInstance) {
    
        return SharedPtrEntityMod( new DrawMod(entity, modelInstance));
    }
    
    EntityMods::DrawMod::DrawMod(ManagedEntity _owningEntity, PlushGraphics::ManagedModelInstance modelInstance)
        : EntityMod(_owningEntity),
          linkedDrawable(createNeededDrawable(_owningEntity, modelInstance))
    {
    }
    
    PlushGraphics::ManagedDrawable EntityMods::DrawMod::createNeededDrawable(ManagedEntity entity, PlushGraphics::ManagedModelInstance modelInstance) {
        PlushGraphics::DrawableSpec newDrawableSpec(EngineUniformResolvers::EntityUniformResolver(entity), modelInstance);
    
        return PlushGraphics::GlobalGraphicsState::getDrawable(PlushGraphics::GlobalGraphicsState::loadDrawable(newDrawableSpec));
    }
}


