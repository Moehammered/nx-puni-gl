#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>

#include <EGL/egl.h>    // EGL library
#include <EGL/eglext.h> // EGL extensions
#include <glad/glad.h>  // glad library (OpenGL loader)
#include "stb_image.h"
#include "OpenGLLoader.h"
#include "Input.h"
#include "Timer.h"
#include "FPSScene.h"

//-----------------------------------------------------------------------------
// nxlink support
//-----------------------------------------------------------------------------

#define ENABLE_NXLINK

#ifndef ENABLE_NXLINK
#define TRACE(fmt,...) ((void)0)
#else
#include <unistd.h>
#define TRACE(fmt,...) printf("%s: " fmt "\n", __PRETTY_FUNCTION__, ## __VA_ARGS__)


static int s_nxlinkSock = -1;

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

//-----------------------------------------------------------------------------
// Main program
//-----------------------------------------------------------------------------

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

int main(int argc, char* argv[])
{
    // Set mesa configuration (useful for debugging)
    setMesaConfig();

    // Initialize EGL on the default window
    // Load OpenGL routines using glad
    puni::OpenGLLoader* glInstance = puni::OpenGLLoader::Instance();
    if(!glInstance->initialiseOpenGL())
        return EXIT_FAILURE;
    else
        printf("Initialised GL successfully!\n\n");

    
    Result rc = romfsInit();
    if (R_FAILED(rc))
        printf("romfsInit: %08X\n", rc);
    else
    {
        printf("romfs Init Successful!\n");
    }

    // Initialize our scene
    sceneInit();

    puni::Input::Initialise();
    puni::Timer::Tick();
    // Main graphics loop
    while (appletMainLoop())
    {
        // Get and process input
        puni::Input::RecordState();
        puni::Timer::Tick();

        if(puni::Input::IsKeyReleased(KEY_PLUS))
            break;

        fpsGame->update();

        // Render stuff!
        sceneRender();

        eglSwapBuffers(glInstance->Display(), glInstance->Surface());
    }

    // Deinitialize our scene
    sceneExit();
    printf("Scene destroyed.\n\n");
    // Deinitialize EGL
    glInstance->DestroySelf();
    printf("GL destroyed.\n\n");
    
    return EXIT_SUCCESS;
}
