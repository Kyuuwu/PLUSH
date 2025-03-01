#ifndef WINDOWSPEC_HPP
#define WINDOWSPEC_HPP

#include <string>

namespace PlushGraphics {
    class WindowSpec{
        public:
            WindowSpec(){}

            WindowSpec(std::string _name) : windowName(_name){}

            double getWindowWidth() const { return windowWidth; }
            double getWindowHeight() const { return windowHeight; }
            std::string getWindowName() const { return windowName; }

        private:
            double windowWidth = 800;
            double windowHeight = 600;
            std::string windowName = "Default Window Name";

            // bool shareContext = false;
    };
}

#endif // WINDOWSPEC_HPP
