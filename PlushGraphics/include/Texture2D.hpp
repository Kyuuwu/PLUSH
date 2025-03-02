#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include "PlushGraphics.hpp"
#include "Texture2DIdentifier.hpp"

namespace PlushGraphics {
    class Texture2D{
        public:
            using Spec = Texture2DSpec;
            using Identifier = Texture2DIdentifier;

            Texture2D(Texture2DSpec spec);
            ~Texture2D();

            Texture2D(const Texture2D&) = delete;
            Texture2D& operator=(const Texture2D&) = delete;
            Texture2D(Texture2D&&) = delete;
            Texture2D& operator=(Texture2D&&) = delete;

            Texture2DIdentifier getIdentifier() const { return identifier; }

            void bindToTextureUnit(u_int32_t textureUnit);

        private:
            Texture2DIdentifier identifier;

            textureReferenceID textureRefID;
    };
}

#endif // TEXTURE2D_HPP
