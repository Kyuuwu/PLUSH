#ifndef ENTITYIDENTIFIER_HPP
#define ENTITYIDENTIFIER_HPP

#include "EntitySpec.hpp"

namespace PlushEngine {
    class EntityIdentifier{
        public:
            EntityIdentifier();

            EntityIdentifier(EntitySpec spec):
                EntityIdentifier(){
                    #pragma unused(spec)
                }

            bool operator<(const EntityIdentifier other) const{
                return uniqueID < other.uniqueID;
            }

        private:
            entityID_t uniqueID;
    };
}

#endif // ENTITYIDENTIFIER_HPP
