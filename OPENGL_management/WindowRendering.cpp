#include "OPENGL_management_includes.h"
#include "OPENGL_includes.h"

namespace OPENGL_management {
    void clearWindow(Window *w, float r, float g, float b, float a){
        if(!(w->WindowActive())){
            throw WINDOW_NOT_ACTIVE;
        }

        glfwMakeContextCurrent(w->getWindowPointer());

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
    }
}