#include "ManagedObject.hpp"
#include "PlushEngine.hpp"
#include "Scene.hpp"
#include "Window/ManagedWindow.hpp"

namespace PlushEngine {
    class ManagedScene : public PlushUtil::ManagedObject<Scene>{
        public:
            using Object = Scene;

            ManagedScene(ManagedScene&& other) noexcept:
                PlushUtil::ManagedObject<Scene>(std::move(other))
            {}

            ManagedScene(const ManagedScene& other):
                PlushUtil::ManagedObject<Scene>(other)
            {}

            template <typename T>
            ManagedScene(T&& arg):
                PlushUtil::ManagedObject<Scene>(std::forward<T>(arg)){}

            template <typename T>
            ManagedScene& operator=(T&& arg){
                PlushUtil::ManagedObject<Scene>::operator=(std::forward<T>(arg));
                return *this;
            }

            void runLogicUpdate(){
                (*this)->_runLogicUpdate();
            }

            void loadOntoWindow(PlushGraphics::ManagedWindow window){
                (*this)->_loadOntoWindow(window);
            }

            SceneIdentifier getIdentifier() const{
                return (*this)->getIdentifier();
            }
    };
}