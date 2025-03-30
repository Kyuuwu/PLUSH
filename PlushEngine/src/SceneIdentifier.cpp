#include "Scene/SceneIdentifier.hpp"
#include "GlobalEngineState.hpp"

namespace PlushEngine {

    SceneIdentifier::SceneIdentifier()
        : uniqueID(GlobalEngineState::getNextUniqueSceneID())
    {
        
    }

}