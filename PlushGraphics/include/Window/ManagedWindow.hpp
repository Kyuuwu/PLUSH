#ifndef MANAGEDWINDOW_HPP
#define MANAGEDWINDOW_HPP

#include "GraphicsLayer/ManagedGraphicsLayer.hpp"
#include "WindowSpec.hpp"
#include "ManagedObject.hpp"
#include "Window.hpp"
#include <memory>

namespace PlushGraphics {
    class ManagedWindow : public PlushUtil::ManagedObject<Window>{
        public:
            friend class GlobalGraphicsState;
            friend class WindowRegistry;

            ManagedWindow(ManagedWindow&& other) noexcept:
                PlushUtil::ManagedObject<Window>(std::move(other))
            {}

            ManagedWindow(const ManagedWindow& other):
                PlushUtil::ManagedObject<Window>(other)
            {}

            template <typename T>
            ManagedWindow(T&& arg) :
                PlushUtil::ManagedObject<Window>(std::forward<T>(arg)){}

            template <typename T>
            ManagedWindow& operator=(T&& arg){
                PlushUtil::ManagedObject<Window>::operator=(std::forward<T>(arg));
                return *this;
            }

            using Object = Window;

            bool getWindowShouldClose(){
                return (*this)->_getWindowShouldClose();
            }

            void swapBuffers(){
                (*this)->_swapBuffers();
            }

            void switchContextToWindow(){
                (*this)->_switchContextToWindow();
            }

            void addGraphicsLayer(ManagedGraphicsLayer layer){
                (*this)->_addGraphicsLayer(layer);
            }

            void clearGraphicsLayers(){
                (*this)->_clearGraphicsLayers();
            }

            void performDrawCycle(){
                (*this)->_performDrawCycle();
            }

            void updateWindowSize(int width, int height){
                (*this)->_updateWindowSize(width, height);
            }

            double getAspectRatio(){
                return (*this)->_getAspectRatio();
            }

            protected:
                void runAfterCreationFromSpec() override;
    };
}

#endif // MANAGEDWINDOW_HPP
