#include "Entity/EntityIdentifier.hpp"
#include "GlobalEngineState.hpp"
#include "PlushEngine.hpp"

namespace PlushEngine {

    EntityIdentifier::EntityIdentifier()
    {
        uniqueID = GlobalEngineState::getNextUniqueEntityID();
    }
    
}