#ifndef MANAGEDGRAPHICSLAYER_HPP
#define MANAGEDGRAPHICSLAYER_HPP

#include "Drawable/ManagedDrawable.hpp"
#include "GraphicsLayer/GraphicsLayer.hpp"
#include "ManagedObject.hpp"
#include "Shader/ManagedShader.hpp"
#include <set>

namespace PlushGraphics {
    class ManagedGraphicsLayer : public PlushUtil::ManagedObject<GraphicsLayer>{
        public:

            ManagedGraphicsLayer(ManagedGraphicsLayer&& other) noexcept:
            PlushUtil::ManagedObject<GraphicsLayer>(std::move(other))
            {}

            ManagedGraphicsLayer(const ManagedGraphicsLayer& other):
                PlushUtil::ManagedObject<GraphicsLayer>(other)
            {}

            template <typename T>
            ManagedGraphicsLayer(T&& arg):
                PlushUtil::ManagedObject<GraphicsLayer>(std::forward<T>(arg)){}

            template <typename T>
            ManagedGraphicsLayer& operator=(T&& arg){
                PlushUtil::ManagedObject<GraphicsLayer>::operator=(std::forward<T>(arg));
                return *this;
            }

            using Object = GraphicsLayer;

            void performDrawCycle(){
                (*this)->_performDrawCycle();
            }

            void addDrawable(ManagedDrawable drawable){
                (*this)->_addDrawable(drawable);
            }

            std::set<ManagedShader> getNecessaryShaders(){
                return (*this)->_getNecessaryShaders();
            }
    };
}

#endif // MANAGEDGRAPHICSLAYER_HPP
