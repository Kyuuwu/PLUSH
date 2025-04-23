#ifndef ENTITYSTATUS_HPP
#define ENTITYSTATUS_HPP
#include "PlushEngine.hpp"
#include "DataStructures/PositionsAndRotations.hpp"

#include <optional>
namespace PlushEngine {
    class EntityStatus{
        public:
            DataStructures::CoordinateState2D& Coords2D() { 
                if(!_coords2D.has_value()){
                    _coords2D = DataStructures::CoordinateState2D();
                }
                return *_coords2D; 
            }

        private:
            std::optional<DataStructures::CoordinateState2D> _coords2D;
            std::optional<DataStructures::CoordinateState3D> _coords3D;
    };
}

#endif // ENTITYSTATUS_HPP
