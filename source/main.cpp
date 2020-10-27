#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#ifdef __SWITCH__
#include <switch.h>
// #include <EGL/egl.h>    // EGL library
// #include <EGL/eglext.h> // EGL extensions
#endif
// #include <glad/glad.h>  // glad library (OpenGL loader)
#include "stb_image.h"

/// my stuff

#include "OpenGLLoader.h"
#include "Input.h"
#include "Timer.h"
#include "FPSScene.h"
#include <thread>
//-----------------------------------------------------------------------------
// nxlink support
//-----------------------------------------------------------------------------
#define ENABLE_NXLINK

#ifndef ENABLE_NXLINK
#define TRACE(fmt,...) ((void)0)
#else
#include <unistd.h>
#define TRACE(fmt,...) printf("%s: " fmt "\n", __PRETTY_FUNCTION__, ## __VA_ARGS__)

#ifdef __SWITCH__
static int s_nxlinkSock = -1;
#endif

puni::FPSScene* fpsGame;

// void updateInput(puni::Transform& tr, float deltaTime)
// {
//     if(puni::Input::IsKeyHeld(KEY_Y))
//         tr.rotate(glm::vec3(0.0f,0.0f,1.0f), movementSpeed * deltaTime);
//     if(puni::Input::IsKeyHeld(KEY_B))
//         tr.rotate(glm::vec3(0,0,1), -movementSpeed * deltaTime);

//     if(puni::Input::IsKeyPressed(KEY_X))
//         movementSpeed = movementSpeed + 0.5f < 10 ? movementSpeed+0.5f : movementSpeed;
//     else if(puni::Input::IsKeyPressed(KEY_B))
//         movementSpeed = movementSpeed - 0.5f > 1 ? movementSpeed-0.5f : movementSpeed;
    
//     if(puni::Input::IsKeyHeld(KEY_UP))
//         tr.position += tr.Up() * movementSpeed * deltaTime;
//     else if(puni::Input::IsKeyHeld(KEY_DOWN))
//         tr.position -= tr.Up() * movementSpeed * deltaTime;

//     if(puni::Input::IsKeyHeld(KEY_RIGHT))
//         tr.position += tr.Right() * movementSpeed * deltaTime;
//     else if(puni::Input::IsKeyHeld(KEY_LEFT))
//         tr.position -= tr.Right() * movementSpeed * deltaTime;

//     if(puni::Input::IsKeyHeld(KEY_ZL))
//         tr.position += tr.Forward() * movementSpeed * deltaTime;
//     else if(puni::Input::IsKeyHeld(KEY_ZR))
//         tr.position -= tr.Forward() * movementSpeed * deltaTime;
// }

#ifdef __SWITCH__
static void initNxLink()
{
    if (R_FAILED(socketInitializeDefault()))
        return;

    s_nxlinkSock = nxlinkStdio();
    if (s_nxlinkSock >= 0)
        TRACE("printf output now goes to nxlink server");
    else
        socketExit();
}

static void deinitNxLink()
{
    if (s_nxlinkSock >= 0)
    {
        close(s_nxlinkSock);
        socketExit();
        s_nxlinkSock = -1;
    }
}

extern "C" void userAppInit()
{
    initNxLink();
}

extern "C" void userAppExit()
{
    deinitNxLink();
}
#endif
#endif

//-----------------------------------------------------------------------------
// Main program
//-----------------------------------------------------------------------------
#ifdef __SWITCH__
static void setMesaConfig()
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

static void sceneInit()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


    fpsGame = new puni::FPSScene();
    fpsGame->initialise();
}

static void sceneRender()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    fpsGame->draw();
}

static void sceneExit()
{
    fpsGame->cleanup();
    delete fpsGame;
}

void TestBitShifting()
{
    using namespace std;

    unsigned int val1 = UINT_MAX;
    unsigned int val2 = val1 / 7;

    cout << setbase(16);

    cout << "UINT HEX: " << val1 << ", " << val2 << endl;

    cout << "Expected: " << val1 << val2 << endl;
    unsigned long long valPair1 = val1;
    valPair1 = valPair1 << 32;
    valPair1 = valPair1 | val2;
    cout << "LONG LONG PAIRED: " << valPair1 << endl;

    unsigned short short1 = UINT16_MAX;
    unsigned short short2 = short1 / 3;
    cout << "SHORT HEX: " << short1 << ", " << short2 << endl;

    cout << "Expected: " << short1 << short2 << endl;
    unsigned int valPair2 = short1;
    valPair2 = valPair2 << 16;
    valPair2 = valPair2 | short2;
    cout << "INT PAIRED: " << valPair2 << endl;

    cout << setbase(10);
}

int main(int argc, char* argv[])
{
    // Set mesa configuration (useful for debugging)
#ifdef __SWITCH__
    setMesaConfig();
    Result rc = romfsInit();
    if (R_FAILED(rc))
        printf("romfsInit: %08X\n", rc);
    else
        printf("romfs Init Successful!\n");
#endif
    // Initialize EGL on the default window
    // Load OpenGL routines using glad
    puni::OpenGLLoader& glInstance = puni::OpenGLLoader::Instance();
    if(!glInstance.initialiseOpenGL())
    {
        std::cout << "Initialised GL FAILED!\n" << std::endl;
        return EXIT_FAILURE;
    }
    else
        std::cout << "Initialised GL successfully!\n" << std::endl;

    // Initialize our scene
    sceneInit();

    TestBitShifting();

    puni::Input::Initialise();
    glfwSetKeyCallback(glInstance.getWindow(), puni::Input::StoreKeyState);
    glfwSetInputMode(glInstance.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    puni::Timer::Tick();

    //crude 'frame limiter'
    double desiredFrameTime = 1/60.0;

    const int timePoints = 240;
    double times[timePoints];
    double sleepTimes[timePoints];
    int timeIndex = 0;
    int sleepIndex = 0;

    while (!glfwWindowShouldClose(glInstance.getWindow()))
    {
        // Get and process input
        puni::Timer::Tick();

        glfwPollEvents();
        puni::Input::RecordMouseMovement();
        puni::Input::RecordGamepads();
        if(puni::Input::IsKeyReleased(GLFW_KEY_ESCAPE) || puni::Input::IsButtonReleased(GLFW_GAMEPAD_BUTTON_START))
            glfwSetWindowShouldClose(glInstance.getWindow(), true);
        
        fpsGame->update();

        // Render stuff!
        sceneRender();
        glfwSwapBuffers(glInstance.getWindow());
        puni::Input::RecordKeys();

        times[timeIndex++] = puni::Timer::DeltaTime();
        if(timeIndex >= timePoints)
        {
            std::cout << "Average FPS over " << timePoints << " frames: ";
            auto total = 0.0;
            for(auto i = 0; i < timePoints; ++i)
                total += times[i];

            std::cout << timePoints/total << " frames / sec" << std::endl;
            timeIndex = 0;
        }

        /// TEMPORARY SOLUTION -- The program runs as fast as possible, hogging resources and increasing power usage
        /// Sleeping for the remainder of the excess frame is temporary
        /// Later on implement a frame limiter
        auto delta = puni::Timer::DeltaTime();
        auto diff = desiredFrameTime - delta;
        if(diff > 0)
        {
            sleepTimes[sleepIndex++] = diff;
            if(sleepIndex >= timePoints)
            {
                std::cout << "Average sleep time over " << timePoints << " frames: ";
                auto average = 0.0;
                for(auto i = 0; i < timePoints; ++i)
                    average += sleepTimes[i];

                std::cout << average/timePoints * 1000 << "ms" << std::endl;
                sleepIndex = 0;
            }
            auto dur = std::chrono::duration<double>(diff);
            std::this_thread::sleep_for(dur);
        }
    }

    std::cout << "Elapsed run time: " << puni::Timer::ElapsedTime() << " seconds" << std::endl;
    std::cout << "Size of int: " << sizeof(int) << std::endl;
    std::cout << "Size of long long: " << sizeof(long long) << std::endl;
    std::cout << "Size of double: " << sizeof(double) << std::endl;
    std::cout << "Size of long double: " << sizeof(long double) << std::endl;
    std::cout << "Size of size_t: " << sizeof(size_t) << std::endl;
    if(sizeof(size_t) == 4)
        std::cout << "size_t is 4 bytes. Most likely on a 32bit architecture." << std::endl;
    else if(sizeof(size_t) == 8)
        std::cout << "size_t is 8 bytes. Most likely on a 64bit architecture." << std::endl;
    else
        std::cout << "size_t is " << sizeof(size_t) << " bytes(" << sizeof(size_t)*8 << "bits). Unknown architecture." << std::endl;

    std::cout << "Max Hardware Concurrency Threads: " << std::thread::hardware_concurrency() << std::endl;        
    // Deinitialize our scene
    sceneExit();

    puni::Shader::CleanUpShaderCache();
    return EXIT_SUCCESS;
}
