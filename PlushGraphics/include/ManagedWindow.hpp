#ifndef MANAGEDWINDOW_HPP
#define MANAGEDWINDOW_HPP

#include "WindowSpec.hpp"
#include "ManagedObject.hpp"
#include "Window.hpp"

namespace PlushGraphics {
    class ManagedWindow : public PlushUtil::ManagedObject<Window>{
        public:
            friend class GlobalGraphicsState;

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
    };
}

#endif // MANAGEDWINDOW_HPP
