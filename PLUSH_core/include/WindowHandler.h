#include <memory>
#include <vector>
#include <string>

#include "KeyStatus.h"

namespace OPENGL_management {
    class Window;
}

namespace PLUSH {
    class DrawableLayer;
    class Standard_Layer;

    class WindowHandler{
        public:
            WindowHandler(std::string name);

            void addDrawableLayer(std::shared_ptr<DrawableLayer> newLayer);
            void addStandardLayer(std::shared_ptr<Standard_Layer> newLayer);

            void setClearColor(float r, float g, float b);

            void setDepthTest(bool depthTest);

            void draw();

            bool ShouldClose();

            void Close();

            float getAspectRatio();
            float getInverseAspectRatio();

            double getMouseX();
            double getMouseY();
            double getMouseYAspectScaled();

            PLUSH_helpers::KeyboardStatus* getKeyboardStatusPointer();
            PLUSH_helpers::MouseStatus* getMouseStatusPointer();

        private:
            std::shared_ptr<OPENGL_management::Window> window;

            float clearColor[3] = {0.5f, 0.5f, 0.5f};

            std::vector<std::shared_ptr<DrawableLayer>> layers;
            std::vector<std::shared_ptr<Standard_Layer>> standard_layers;
    };
}