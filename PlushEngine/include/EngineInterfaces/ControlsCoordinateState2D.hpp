#include "PlushEngine.hpp"

namespace PlushEngine {
    namespace EngineInterfaces {
        class ControlsCoordinateState2D{
            public:
                virtual void setPosition2D(double x, double y) = 0;
                virtual void setRotation2D(double angle) = 0;
        };
    }
}