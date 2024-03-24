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

    void enableDepthTest(Window *w){
        if(!(w->WindowActive())){
            throw WINDOW_NOT_ACTIVE;
        }

        glfwMakeContextCurrent(w->getWindowPointer());

        glEnable(GL_DEPTH_TEST);
        // glDepthFunc(GL_EQUAL); 
    }

    void disableDepthTest(Window *w){
        if(!(w->WindowActive())){
            throw WINDOW_NOT_ACTIVE;
        }

        glfwMakeContextCurrent(w->getWindowPointer());

        glDisable(GL_DEPTH_TEST);
    }
}