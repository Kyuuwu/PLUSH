#ifndef DRAWABLEREGISTRY_HPP
#define DRAWABLEREGISTRY_HPP

#include "PlushGraphics.hpp"
#include "Registry.hpp"
#include "ManagedDrawable.hpp"

namespace PlushGraphics {
    class DrawableRegistry : public PlushUtil::Registry<ManagedDrawable>{

    };
}

#endif // DRAWABLEREGISTRY_HPP
