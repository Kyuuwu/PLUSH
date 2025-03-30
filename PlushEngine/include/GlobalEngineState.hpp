#ifndef GLOBALENGINESTATE_HPP
#define GLOBALENGINESTATE_HPP

#include "PlushEngine.hpp"
#include "Entity/EntityRegistry.hpp"
#include "Scene/SceneRegistry.hpp"

namespace PlushEngine {
    class GlobalEngineState{
        public:
            inline static EntityRegistry entityRegistry;
            inline static SceneRegistry sceneRegistry;

            static ManagedEntity getEntity(EntityIdentifier identifier){
                return entityRegistry.getItem(identifier);
            }
            static ManagedScene getScene(SceneIdentifier identifier){
                return sceneRegistry.getItem(identifier);
            }

            static bool isEntityLoaded(EntityIdentifier identifier){
                return entityRegistry.isItemLoaded(identifier);
            }
            static bool isSceneLoaded(SceneIdentifier identifier){
                return sceneRegistry.isItemLoaded(identifier);
            }

            static EntityIdentifier loadEntity(EntitySpec spec){
                return entityRegistry.loadItem(spec);
            }
            static SceneIdentifier loadScene(SceneSpec spec){
                return sceneRegistry.loadItem(spec);
            }

            
            static entityID_t getNextUniqueEntityID(){
                entityID_t result = nextUniqueEntityID;
                nextUniqueEntityID++;
                return result;
            }
            
            static sceneID_t getNextUniqueSceneID(){
                sceneID_t result = nextUniqueSceneID;
                nextUniqueSceneID++;
                return result;
            }

        private:
            inline static entityID_t nextUniqueEntityID = 0;
            inline static sceneID_t nextUniqueSceneID = 0;
    };
}

#endif // GLOBALENGINESTATE_HPP
