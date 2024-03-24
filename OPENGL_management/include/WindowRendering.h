class Window;

namespace OPENGL_management {
    void clearWindow(Window* w, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

    void enableDepthTest(Window* w);
    void disableDepthTest(Window* w);

}