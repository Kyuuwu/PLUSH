#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "OpenGL.h"
#include "PlushGraphics.hpp"

namespace PlushGraphics {
    class Window{
        public:
            Window(WindowBuilder windowbuilder);

        private:
            GLFWwindow* windowPointer;
    };
}

#endif // WINDOW_HPP
