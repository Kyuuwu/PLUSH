#ifndef SHADERUNIFORMSLOTFULFILLMENTSTATE_HPP
#define SHADERUNIFORMSLOTFULFILLMENTSTATE_HPP

#include "PlushGraphics.hpp"

namespace PlushGraphics {
    namespace ShaderMetadata {
        enum class FulfillmentTimeFlag{
            UNFULFILLED,
            FULFILLED_IN_PAST_FRAME,
            FULFILLED_THIS_FRAME
        };
    
        enum class FulfillmentLevelFlag{
            LEVEL_0, // convention: fulfilled at window-level
            LEVEL_1, // convention: fulfilled at layer-level
            LEVEL_2, // convention: fulfilled at entity-level
            LEVEL_3, // convention: fulfilled to be overriden within entity uniform resolution
            LEVEL_Z // special cases and default
        };
    
        class ShaderUniformSlotFulfillmentState{
            public:
                FulfillmentTimeFlag lastFulfillmentTime = FulfillmentTimeFlag::UNFULFILLED;
                FulfillmentLevelFlag lastFulfillmentLevel = FulfillmentLevelFlag::LEVEL_Z;
    
            private:
        };
    }
}

#endif // SHADERUNIFORMSLOTFULFILLMENTSTATE_HPP
