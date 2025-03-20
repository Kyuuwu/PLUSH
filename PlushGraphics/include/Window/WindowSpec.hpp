#ifndef WINDOWSPEC_HPP
#define WINDOWSPEC_HPP

#include <string>
#include "PlushGraphics.hpp"
#include "UniformResolver.hpp"
#include "WindowSettings.hpp"

namespace PlushGraphics {
    class WindowSpec{
        public:
            WindowSpec(){}

            WindowSpec(WindowSettings _settings) : settings(_settings){}

            friend class Window;

            template<UniResDerived T>
            WindowSpec(T&& ur, WindowSettings _settings) : 
                settings(_settings),
                resolver(new T(std::move(ur))) {}

            template<UniResDerived T>
            WindowSpec(const T& ur, WindowSettings _settings) : 
                settings(_settings),
                resolver(new T(ur)) {}

            WindowSpec(const WindowSpec& other):
                settings(other.settings),
                resolver(other.resolver->duplicateSelf()){}

            double getWindowWidth() const { return settings.windowWidth; }
            double getWindowHeight() const { return settings.windowHeight; }
            std::string getWindowName() const { return settings.windowName; }

        private:
            WindowSettings settings;

            std::unique_ptr<UniformResolver> resolver;

            // bool shareContext = false;
    };
}

#endif // WINDOWSPEC_HPP
