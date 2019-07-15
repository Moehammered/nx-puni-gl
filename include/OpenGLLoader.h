#ifndef SWITCH__GLLOADER__H_
#define SWITCH__GLLOADER__H_

#include <switch.h>
#include <EGL/egl.h>    // EGL library
#include <EGL/eglext.h> // EGL extensions
#include <glad/glad.h>  // glad library (OpenGL loader)
#include <string>

namespace puni
{
    class OpenGLLoader
    {
        public:
            static OpenGLLoader* const Instance();

            unsigned int ScreenWidth();
            unsigned int ScreenHeight();
            bool initialiseOpenGL();
            void initMesaConfig();
            EGLDisplay& Display();
            EGLContext& Context();
            EGLSurface& Surface();
            void DestroySelf();

        private:
            OpenGLLoader();
            ~OpenGLLoader();

            ///info variables
            int minVersion, majVersion, glProfile;
            unsigned int screenWidth, screenHeight;
            std::string title;

            ///context variables
            NWindow* windowHandle;
            EGLDisplay display;
            EGLContext context;
            EGLSurface surface;

            ///singleton instance
            static OpenGLLoader* _instance;

            bool initEGL();
    };
}

#endif