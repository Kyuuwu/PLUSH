 #include <iostream>
 #include "OPENGL_includes.h"

 #include "WindowSetup.h"

namespace OPENGL_management{
    GLFWwindow* createWindow(int width, int height, const char* window_title){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

        if(window == NULL){
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            throw 1;
        }
        glfwMakeContextCurrent(window);

        if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
            std::cout << "Failed to initialize GLAD" << std::endl;
            throw 2;
        }

        glViewport(0,0,width,height);

        return window;
    }
}