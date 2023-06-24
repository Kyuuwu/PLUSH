#include "Helpers.h"
#include "Exceptions.h"
#include "OPENGL_includes.h"

#include <fstream>
#include <iostream>

namespace PLUSH_helpers {
    std::stringstream getStreamFromFile(std::string path){
        std::ifstream file;
        std::stringstream stream;
        try 
        {
            // open files
            file.open(path);
            // read file's buffer contents into streams
            stream << file.rdbuf();
            // close file handlers
            file.close();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::MODEL::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
            throw(FILE_READ_ERROR); 
        }

        return stream;
    }

    KeyboardStatus getFreshKeyboard(){
        KeyboardStatus keyboard;

        for(int i = 0; i < num_keys; i++){
            keyboard.keystatus[i] = RELEASED;
        }

        return keyboard;
    }

    Key getKeyFromOpenGL_Key(int opengl_key){
        GLenum key_enum = (GLenum) opengl_key;
        switch(key_enum){
            case GLFW_KEY_ESCAPE:
                return KEY_ESCAPE;
            case GLFW_KEY_SPACE:
                return KEY_SPACE;
            case GLFW_KEY_UP:
                return KEY_UP;
            case GLFW_KEY_DOWN:
                return KEY_DOWN;
            case GLFW_KEY_RIGHT:
                return KEY_RIGHT;
            case GLFW_KEY_LEFT:
                return KEY_LEFT;
            case GLFW_KEY_A:
                return KEY_A;
            case GLFW_KEY_B:
                return KEY_B;
            case GLFW_KEY_C:
                return KEY_C;
            case GLFW_KEY_D:
                return KEY_D;
            case GLFW_KEY_E:
                return KEY_E;
            case GLFW_KEY_F:
                return KEY_F;
            case GLFW_KEY_G:
                return KEY_G;
            case GLFW_KEY_H:
                return KEY_H;
            case GLFW_KEY_I:
                return KEY_I;
            case GLFW_KEY_J:
                return KEY_J;
            case GLFW_KEY_K:
                return KEY_K;
            case GLFW_KEY_L:
                return KEY_L;
            case GLFW_KEY_M:
                return KEY_M;
            case GLFW_KEY_N:
                return KEY_N;
            case GLFW_KEY_O:
                return KEY_O;
            case GLFW_KEY_P:
                return KEY_P;
            case GLFW_KEY_Q:
                return KEY_Q;
            case GLFW_KEY_R:
                return KEY_R;
            case GLFW_KEY_S:
                return KEY_S;
            case GLFW_KEY_T:
                return KEY_T;
            case GLFW_KEY_U:
                return KEY_U;
            case GLFW_KEY_V:
                return KEY_V;
            case GLFW_KEY_W:
                return KEY_W;
            case GLFW_KEY_X:
                return KEY_X;
            case GLFW_KEY_Y:
                return KEY_Y;
            case GLFW_KEY_Z:
                return KEY_Z;
            default:
                throw(UNRECOGNIZED_KEY);
        }
    }

    void Terminate_GLFW(){
        glfwTerminate();
    }

    void PollEvents_GLFW(){
        glfwPollEvents();
    }

    float GetTime(){
        return glfwGetTime();
    }

    void Set_V_Sync(bool value){
        glfwSwapInterval(value);
    }

    float last_time=0.0;

    void outputTimeElapsed(){
        float currentTime = PLUSH_helpers::GetTime();

        std::cout << currentTime - last_time;

        last_time = currentTime;
    }
}