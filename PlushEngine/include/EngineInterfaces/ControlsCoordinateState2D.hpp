#ifndef CONTROLSCOORDINATESTATE2D_HPP
#define CONTROLSCOORDINATESTATE2D_HPP

namespace PlushEngine {
    namespace EngineInterfaces {
        class ControlsCoordinateState2D{
            public:
                virtual void setPosition2D(double x, double y) = 0;
                virtual void setRotation2D(double angle) = 0;
        };
    }
}

#endif // CONTROLSCOORDINATESTATE2D_HPP
