#ifndef WINDOWREGISTRY_HPP
#define WINDOWREGISTRY_HPP

#include "Registry.hpp"
#include "ManagedWindow.hpp"

namespace PlushGraphics {
    class WindowRegistry : public PlushUtil::Registry<ManagedWindow>{
    };
}

#endif // WINDOWREGISTRY_HPP
