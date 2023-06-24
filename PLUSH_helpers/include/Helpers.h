#include <sstream>

#include <string>

#include "KeyStatus.h"

namespace PLUSH_helpers {
    std::stringstream getStreamFromFile(std::string path);
    KeyboardStatus getFreshKeyboard();
    Key getKeyFromOpenGL_Key(int opengl_key);
    void Terminate_GLFW();
    void PollEvents_GLFW();
    void Set_V_Sync(bool value);
    float GetTime();
    void outputTimeElapsed();
}