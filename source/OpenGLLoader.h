#ifndef SWITCH__GLLOADER__H_
#define SWITCH__GLLOADER__H_

#ifdef __SWITCH__
#include <switch.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#else
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "glad/glad.h"  // glad library (OpenGL loader)
#endif
#include <string>

namespace puni
{
    class OpenGLLoader
    {
        public:
            static OpenGLLoader& Instance();

            unsigned int ScreenWidth();
            unsigned int ScreenHeight();
            bool initialiseOpenGL();
            #ifdef __SWITCH__
            void initMesaConfig();
            #endif
            void setWindowSize(int x, int y);
	        void setWindowResizeEvent(GLFWframebuffersizefun callback);
	        GLFWwindow* const getWindow();

        private:
            OpenGLLoader();
            ~OpenGLLoader();

            ///info variables
            int minVersion, majVersion, glProfile;
            unsigned int screenWidth, screenHeight;
            std::string title;

            GLFWwindow* windowHandle;

            static void onWindowResizeCallback(GLFWwindow* window, int width, int height);
    };
}

#endif