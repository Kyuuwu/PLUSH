#include "PlushEngine.hpp"

namespace PlushEngine {
    namespace DataStructures {
        class Position2D{
            public:
                double x,y = 0;
        };

        class Position3D{
            public:
                double x,y,z = 0;
        };

        class Rotation2D{
            public:
                double angle = 0;
        };

        /// TBD
        class Rotation3D{

        };

        class CoordinateState2D{
            public:
                Position2D position;
                Rotation2D rotation;
        };

        class CoordinateState3D{
            public:
                Position3D position;
                Rotation3D rotation;
        };
    }
}