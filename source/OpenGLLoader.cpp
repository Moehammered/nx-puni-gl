#include "OpenGLLoader.h"
#include <iostream>

// puni::OpenGLLoader* puni::OpenGLLoader::_instance = nullptr;

puni::OpenGLLoader& puni::OpenGLLoader::Instance()
{
    static OpenGLLoader instance;

    return instance;
}

void puni::OpenGLLoader::setWindowSize(int x, int y)
{
	screenHeight = y;
	screenWidth = x;
}

void puni::OpenGLLoader::setWindowResizeEvent(GLFWframebuffersizefun callback)
{
	if(windowHandle)
		glfwSetFramebufferSizeCallback(windowHandle, callback);
}

GLFWwindow* const puni::OpenGLLoader::getWindow()
{
	return windowHandle;
}

void puni::OpenGLLoader::onWindowResizeCallback(GLFWwindow * window, int width, int height)
{
	Instance().screenHeight = height;
	Instance().screenWidth = width;
	glViewport(0, 0, width, height);
}

unsigned int puni::OpenGLLoader::ScreenWidth()
{
    return screenWidth;
}

unsigned int puni::OpenGLLoader::ScreenHeight()
{
    return screenHeight;
}

void glfwcallback_error(int error_code, const char* desc)
{
    std::cout << "GLFW Error: " << error_code << ", " << desc << std::endl;
}

bool puni::OpenGLLoader::initialiseOpenGL()
{
    //initialise glfw
	glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_FALSE);
    if(!glfwInit())
    {
        std::cout << "GLFWInit failed." << std::endl;
        return false;
    }
    
    glfwSetErrorCallback(glfwcallback_error);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, glProfile);

    std::cout << "GLFW CONTEXT VERS MAJ: " << majVersion << std::endl;
    std::cout << "GLFW CONTEXT VERS MIN: " << minVersion << std::endl;
    std::cout << "GLFW OPENGL PROFILE: " << glProfile << std::endl;

    //create the window
    windowHandle = glfwCreateWindow(screenWidth, screenHeight,
        title.c_str(), nullptr, nullptr);
    if (!windowHandle)
    {
        glfwTerminate();
        std::cout << "failed to create window handle" << std::endl;
        return false;
    }

    //make it current
    glfwMakeContextCurrent(windowHandle);

    //load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to load GLAD" << std::endl;
        return false;
    }

    //set the viewport
    glViewport(0, 0, screenWidth, screenHeight);

    setWindowResizeEvent(puni::OpenGLLoader::onWindowResizeCallback);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION);
    std::cout << " || GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    return true;
}

#ifdef __SWITCH__
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
#endif

puni::OpenGLLoader::OpenGLLoader()
{
    screenWidth = 1280;
    screenHeight = 720;
    minVersion = 3;
    majVersion = 4;
    glProfile = GLFW_OPENGL_CORE_PROFILE;

    title = "puni::miniframework-opengl";
}

puni::OpenGLLoader::~OpenGLLoader()
{
    glfwTerminate();
}