#ifndef ENTITYSTATUS_HPP
#define ENTITYSTATUS_HPP
#include "PlushEngine.hpp"
#include "DataStructures/PositionsAndRotations.hpp"

#include <optional>
namespace PlushEngine {
    class EntityStatus{
        public:
            std::optional<DataStructures::CoordinateState2D> coords2D;
            std::optional<DataStructures::CoordinateState3D> coords3D;
    };
}

#endif // ENTITYSTATUS_HPP
