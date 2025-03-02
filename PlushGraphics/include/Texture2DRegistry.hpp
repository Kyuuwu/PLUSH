#ifndef TEXTURE2DREGISTRY_HPP
#define TEXTURE2DREGISTRY_HPP

#include "Registry.hpp"
#include "ManagedTexture2D.hpp"

namespace PlushGraphics {
    class Texture2DRegistry : public PlushUtil::Registry<ManagedTexture2D>{
    };
}

#endif // TEXTURE2DREGISTRY_HPP
