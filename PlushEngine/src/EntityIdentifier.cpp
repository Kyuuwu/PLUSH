#include "Entity/EntityIdentifier.hpp"
#include "GlobalEngineState.hpp"

namespace PlushEngine {

    EntityIdentifier::EntityIdentifier()
    {
        uniqueID = GlobalEngineState::getNextUniqueEntityID();
    }
    
}