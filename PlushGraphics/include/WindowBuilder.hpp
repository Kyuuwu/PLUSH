#ifndef WINDOWBUILDER_HPP
#define WINDOWBUILDER_HPP

#include <string>

namespace PlushGraphics {
    class WindowBuilder{
        public:
            double getWindowWidth() const { return windowWidth; }
            double getWindowHeight() const { return windowHeight; }
            std::string getWindowName() const { return windowName; }

        private:
            double windowWidth = 800;
            double windowHeight = 600;
            std::string windowName = "Default Window Name";
    };
}

#endif // WINDOWBUILDER_HPP
