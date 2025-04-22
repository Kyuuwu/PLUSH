#ifndef CONTROLSCOORDINATESTATE2D_HPP
#define CONTROLSCOORDINATESTATE2D_HPP

namespace PlushEngine {
    namespace EngineInterfaces {
        class ControlsCoordinateState2D{
            public:
                virtual void setPosition2D(double x, double y) = 0;
                virtual void setRotation2D(double angle) = 0;

                template<typename Self>
                Self&& withPosition2D(this Self&& self, double x, double y){
                    self.setPosition2D(x,y);
                    return self;
                }
                template<typename Self>
                Self&& withRotation2D(this Self&& self, double angle){
                    self.setRotation2D(angle);
                    return self;
                }
        };
    }
}

#endif // CONTROLSCOORDINATESTATE2D_HPP
