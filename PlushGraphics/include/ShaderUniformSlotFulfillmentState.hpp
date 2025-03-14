#ifndef SHADERUNIFORMSLOTFULFILLMENTSTATE_HPP
#define SHADERUNIFORMSLOTFULFILLMENTSTATE_HPP

#include "PlushGraphics.hpp"

namespace PlushGraphics {
    enum class FulfillmentFlag{
        UNFULFILLED,
        FULFILLED_LAST_FRAME,
        FULFILLED_THIS_FRAME_BY_WINDOW
    };

    class ShaderMetadata::ShaderUniformSlotFulfillmentState{
        public:
            FulfillmentFlag lastFulfillment = FulfillmentFlag::UNFULFILLED;

        private:
    };
}

#endif // SHADERUNIFORMSLOTFULFILLMENTSTATE_HPP
