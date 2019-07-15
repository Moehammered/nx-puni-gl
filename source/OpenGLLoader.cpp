#include "OpenGLLoader.h"
#include <stdio.h>

void printEGLErrorCode()
{
    printf("EGL error code: %d\n\n", eglGetError());
}

void printError(std::string msg)
{
    printf("ERROR::OPENGLLOADER - %s\n\n", msg.c_str());
}

puni::OpenGLLoader* puni::OpenGLLoader::_instance = nullptr;

puni::OpenGLLoader* const puni::OpenGLLoader::Instance()
{
    if(!_instance)
        _instance = new OpenGLLoader();

    return _instance;
}

EGLDisplay& puni::OpenGLLoader::Display()
{
    return display;
}

EGLSurface& puni::OpenGLLoader::Surface()
{
    return surface;
}

EGLContext& puni::OpenGLLoader::Context()
{
    return context;
}

unsigned int puni::OpenGLLoader::ScreenWidth()
{
    return screenWidth;
}

unsigned int puni::OpenGLLoader::ScreenHeight()
{
    return screenHeight;
}

bool puni::OpenGLLoader::initialiseOpenGL()
{
    windowHandle = nwindowGetDefault();

    if(!windowHandle)
    {
        printf("ERROR::OPENGLLOADER - Window Handle null/failed init.\n\n");
        return false;
    }

    if(initEGL())
    {
        gladLoadGL();
        nwindowGetDimensions(windowHandle, &screenWidth, &screenHeight);
    }
    else
    {
        printError("EGL initialisation failed. Shutting down.");
        return false;
    }

    return true;
}

bool puni::OpenGLLoader::initEGL()
{
    //get display context
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(!display)
    {
        //printf("ERROR::OPENGLLOADER - display failed init/connection.\n\n");
        printError("display failed init/connection.");
        return false;
    }
    //initialise display connection
    eglInitialize(display, &(minVersion), &(majVersion)); //replace with nullptr if errors

    if(eglBindAPI(EGL_OPENGL_API) == EGL_FALSE)
    {
        //printf("ERROR::OPENGLLOADER - API failed to bind.\n\n%d\n\n", eglGetError());
        printError("API failed to bind.");
        //printf("EGL error code: %d\n\n", eglGetError());
        printEGLErrorCode();
        return false;
    }

    //configure EGL framebuffer
    EGLConfig config;
    EGLint numConfigs;
    static const EGLint framebufferAttribList[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_RED_SIZE,     8,
        EGL_GREEN_SIZE,   8,
        EGL_BLUE_SIZE,    8,
        EGL_ALPHA_SIZE,   8,
        EGL_DEPTH_SIZE,   24,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
    };
    eglChooseConfig(display, framebufferAttribList, &config, 1, &numConfigs);

    if(numConfigs == 0)
    {
        printError("No config found.");
        printEGLErrorCode();
        return false;
    }

    //create a GL window surface now
    surface = eglCreateWindowSurface(display, config, windowHandle, nullptr);
    if(!surface)
    {
        printError("GL surface failed creation.");
        printEGLErrorCode();
        return false;
    }

    //create a render context
    static const EGLint contextAttribList[] = {
        EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR, glProfile,
        EGL_CONTEXT_MAJOR_VERSION_KHR, majVersion,
        EGL_CONTEXT_MINOR_VERSION_KHR, minVersion,
        EGL_NONE
    };
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribList);
    if(!context)
    {
        printError("GL Context failed creation.");
        printEGLErrorCode();
        return false;
    }

    //finally setup the current context and make it active
    if(eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
    {
        printError("Making context current messed up somehow.");
        printEGLErrorCode();
        return false;
    }

    //survived the init process
    return true;
}

void puni::OpenGLLoader::DestroySelf()
{
    if(_instance)
        delete _instance;
}

void puni::OpenGLLoader::initMesaConfig()
{
    // Uncomment below to disable error checking and save CPU time (useful for production):
    //setenv("MESA_NO_ERROR", "1", 1);

    // Uncomment below to enable Mesa logging:
    //setenv("EGL_LOG_LEVEL", "debug", 1);
    //setenv("MESA_VERBOSE", "all", 1);
    //setenv("NOUVEAU_MESA_DEBUG", "1", 1);

    // Uncomment below to enable shader debugging in Nouveau:
    //setenv("NV50_PROG_OPTIMIZE", "0", 1);
    //setenv("NV50_PROG_DEBUG", "1", 1);
    //setenv("NV50_PROG_CHIPSET", "0x120", 1);
}

puni::OpenGLLoader::OpenGLLoader()
{
    screenWidth = 800;
    screenHeight = 600;
    minVersion = 3;
    majVersion = 4;
    glProfile = EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR;

    title = "puni::miniframework-opengl";
}

puni::OpenGLLoader::~OpenGLLoader()
{
    printf("Destroying GLLoader\n\n");
    if (display)
    {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context)
        {
            eglDestroyContext(display, context);
            context = nullptr;
        }
        if (surface)
        {
            eglDestroySurface(display, surface);
            surface = nullptr;
        }
        eglTerminate(display);
        display = nullptr;
    }

    // if(_instance)
    //     delete _instance;
    _instance = nullptr;

    printf("Finished destruction\n\n");
}
