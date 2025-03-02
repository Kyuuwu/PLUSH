#ifndef TEXTURE2DIDENTIFIER_HPP
#define TEXTURE2DIDENTIFIER_HPP

#include <string>

namespace PlushGraphics {
    class Texture2DIdentifier{
        public:
            Texture2DIdentifier(std::string name) :
                textureName(name) {}

            bool operator< (const Texture2DIdentifier& other) const {return textureName < other.textureName;}

            std::string getTexture2DName() const { return textureName; }

        private:
            std::string textureName;
    };
}

#endif // TEXTURE2DIDENTIFIER_HPP
