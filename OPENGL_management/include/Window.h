#include <string>

#include "ShaderUniforms.h"
#include <vector>

#include "KeyStatus.h"

class GLFWwindow;

namespace OPENGL_management{

    struct Dimensions{
        int width;
        int height;
    };

    class Window{
        public:
            Window(std::string title = "Default title");

            bool WindowActive();
            bool ShouldClose();

            GLFWwindow* getWindowPointer();

            void Create();
            void Close();
            void Destroy();

            void setTitle(std::string title);
            Dimensions getDimensions();

            float getAspectRatio();
            float getInverseAspectRatio();

            void framebuffer_size_callback(GLFWwindow* window, int width, int height);
            void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
            void mouse_pos_callback(GLFWwindow* window, double x_pos, double y_pos);
            void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

            std::vector<ShaderUniform> getWindowUniforms();
            void recalculateWindowUniforms();

            void swapBuffers();

            PLUSH_helpers::KeyboardStatus* getKeyboardStatusPointer();
            PLUSH_helpers::MouseStatus* getMouseStatusPointer();

            double getMouseX();
            double getMouseY();
            double getMouseYAspectScaled();

        private:
            
            PLUSH_helpers::KeyboardStatus keyboardstatus;

            PLUSH_helpers::MouseStatus mousestatus;

            double mouseX = 0.0;
            double mouseY = 0.0;

            bool windowActive = false;
            GLFWwindow* parentwindow = NULL;
            GLFWwindow* window=NULL;
            std::string window_title="Example Title";
            int window_width=800;
            int window_height=600;

            std::vector<ShaderUniform> window_uniforms;
            bool window_uniforms_up_to_date = false;

    };


}