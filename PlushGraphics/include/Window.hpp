#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "OpenGL.h"
#include "PlushGraphics.hpp"

namespace PlushGraphics {
    class Window{
        public:
            Window(WindowBuilder windowbuilder);
            GLFWwindow* windowPointer;

        private:
    };
}

#endif // WINDOW_HPP
