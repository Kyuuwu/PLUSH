#ifndef SCENEIDENTIFIER_HPP
#define SCENEIDENTIFIER_HPP

#include "PlushEngine.hpp"
#include "SceneSpec.hpp"

namespace PlushEngine {
    class SceneIdentifier{
        public:
            SceneIdentifier();
            SceneIdentifier(SceneSpec spec) : 
                SceneIdentifier() {
                    #pragma unused(spec)
                }

            bool operator<(const SceneIdentifier other) const{
                return uniqueID < other.uniqueID;
            }

        private:
            sceneID_t uniqueID;
    };
}

#endif // SCENEIDENTIFIER_HPP
