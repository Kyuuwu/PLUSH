#ifndef ENTITYSTATUS_HPP
#define ENTITYSTATUS_HPP
#include "PlushEngine.hpp"
#include "DataStructures/PositionsAndRotations.hpp"

#include <optional>
namespace PlushEngine {
    class EntityStatus{
        public:
            std::optional<DataStructures::Position2D> position2D;
            std::optional<DataStructures::Position3D> position3D;
            std::optional<DataStructures::Rotation2D> rotation2D;
    };
}

#endif // ENTITYSTATUS_HPP
