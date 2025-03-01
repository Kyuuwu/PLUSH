#ifndef WINDOWIDENTIFIER_HPP
#define WINDOWIDENTIFIER_HPP

#include <string>

namespace PlushGraphics {
    class WindowIdentifier{
        public:
            WindowIdentifier(std::string _windowName) : windowName(_windowName){}
            bool operator< (const WindowIdentifier& other) const { return windowName < other.windowName;}

            std::string getWindowName() const { return windowName; }

        private:
            std::string windowName;
    };
}

#endif // WINDOWIDENTIFIER_HPP
