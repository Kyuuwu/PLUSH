#ifndef SCENEREGISTRY_HPP
#define SCENEREGISTRY_HPP

#include "PlushEngine.hpp"
#include "Registry.hpp"
#include "ManagedScene.hpp"
#include "SceneIdentifier.hpp"

namespace PlushEngine {
    class SceneRegistry : public PlushUtil::Registry<ManagedScene>{
    };
}

#endif // SCENEREGISTRY_HPP
