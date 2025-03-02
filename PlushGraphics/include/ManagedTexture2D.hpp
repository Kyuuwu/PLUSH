#ifndef MANAGEDTEXTURE2D_HPP
#define MANAGEDTEXTURE2D_HPP

#include "ManagedObject.hpp"
#include "Texture2D.hpp"
#include "Texture2DSpec.hpp"

namespace PlushGraphics {
    class ManagedTexture2D: public PlushUtil::ManagedObject<Texture2D>{
        public:
            ManagedTexture2D(ManagedTexture2D&& other) noexcept:
            PlushUtil::ManagedObject<Texture2D>(std::move(other))
            {}

            ManagedTexture2D(const ManagedTexture2D& other):
                PlushUtil::ManagedObject<Texture2D>(other)
            {}

            template <typename T>
            ManagedTexture2D(T&& arg):
                PlushUtil::ManagedObject<Texture2D>(std::forward<T>(arg)){}

            template <typename T>
            ManagedTexture2D& operator=(T&& arg){
                return PlushUtil::ManagedObject<Texture2D>::operator=(std::forward<T>(arg));
            }

            using Object = Texture2D;

            void bindToTextureUnit(uint32_t textureUnit){
                (*this)->bindToTextureUnit(textureUnit);
            }

        private:
    };
}

#endif // MANAGEDTEXTURE2D_HPP
