#ifndef TEXTURE2DSPEC_HPP
#define TEXTURE2DSPEC_HPP

#include <string>

namespace PlushGraphics {
    class Texture2DSpec{
        public:
            Texture2DSpec(std::string fileName):
            textureFileName(fileName) {}

            std::string getTexture2DFileName() const { return textureFileName; }

        private:
            std::string textureFileName;
    };
}

#endif // TEXTURE2DSPEC_HPP
