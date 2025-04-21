#ifndef MANAGEDDRAWABLE_HPP
#define MANAGEDDRAWABLE_HPP

#include "ManagedObject.hpp"
#include "Drawable.hpp"
#include "Shader/ManagedShader.hpp"

namespace PlushGraphics {
    class ManagedDrawable : public PlushUtil::ManagedObject<Drawable>{
        public:
            ManagedDrawable(ManagedDrawable&& other) noexcept:
                PlushUtil::ManagedObject<Drawable>(std::move(other))
            {}

            ManagedDrawable(const ManagedDrawable& other):
                PlushUtil::ManagedObject<Drawable>(other)
            {}

            template <typename T>
            ManagedDrawable(T&& arg):
                PlushUtil::ManagedObject<Drawable>(std::forward<T>(arg)){}

            template <typename T>
            ManagedDrawable& operator=(T&& arg){
                PlushUtil::ManagedObject<Drawable>::operator=(std::forward<T>(arg));
                return *this;
            }

            using Object = Drawable;

            void draw(){
                (*this)->_draw();
            }

            void setModelInstance(ManagedModelInstance modelInstance){
                (*this)->_setModelInstance(modelInstance);
            }

            ManagedShader getModelInstanceShader(){
                return (*this)->_getModelInstanceShader();
            }


            template<UniResDerived T>
            void setUniformResolver(T&& _ur){
                (*this)->_setUniformResolver(std::forward<T>(_ur));
            }

        private:
    };
}

#endif // MANAGEDDRAWABLE_HPP
