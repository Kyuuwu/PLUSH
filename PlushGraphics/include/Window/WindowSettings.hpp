#ifndef WINDOWSETTINGS_HPP
#define WINDOWSETTINGS_HPP

#include "PlushGraphics.hpp"
#include "glm/glm.hpp"

namespace PlushGraphics{
    class WindowSettings{
        public:
            double windowWidth = 800;
            double windowHeight = 600;
            std::string windowName = "Default Window Name";

            glm::vec4 clearColor = glm::vec4(0.2, 0.3, 0.3, 1.0);
    };
}


#endif // WINDOWSETTINGS_HPP
