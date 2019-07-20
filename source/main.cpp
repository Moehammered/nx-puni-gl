#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>

#include <EGL/egl.h>    // EGL library
#include <EGL/eglext.h> // EGL extensions
#include <glad/glad.h>  // glad library (OpenGL loader)
// #define GLM_FORCE_PURE
// #include <glm/vec3.hpp>
// #include <glm/vec4.hpp>
// #include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include "OpenGLLoader.h"
#include "Input.h"
#include "Timer.h"
#include "Transform.h"
#include "PrimitiveShapes.h"
#include "VertexArrayObject.h"
#include "FileLoader.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "ObjectAllocator.h"
#include "GameObject.h"
#include "UpdateableComponent.h"
#include "ComponentUpdateQueue.h"
//-----------------------------------------------------------------------------
// nxlink support
//-----------------------------------------------------------------------------

#define ENABLE_NXLINK

#ifndef ENABLE_NXLINK
#define TRACE(fmt,...) ((void)0)
#else
#include <unistd.h>
#define TRACE(fmt,...) printf("%s: " fmt "\n", __PRETTY_FUNCTION__, ## __VA_ARGS__)


// constexpr auto TAU = glm::two_pi<float>();
static int s_nxlinkSock = -1;

unsigned int shaderTransfromLoc;
puni::Transform triTr;
puni::Mesh tri;
puni::VertexArrayObject *vao;
float movementSpeed = 5;
float rotationSpeed = 360;
std::string vertShaderPath = "romfs:/shaders/transform-coltex-shader.vs";
std::string fragShaderPath = "romfs:/shaders/coltex-shader.fs";
std::string texturePath = "romfs:/awesomeface.png";
puni::Shader colourShader;
puni::Camera sceneCam;
puni::Texture faceImg;
puni::Object* obj;
puni::GameObject testGO;
///extra experiment functions
void updateTransform(GLuint& trLoc, glm::mat4 mat)
{
    glUniformMatrix4fv(trLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

void updateInput(puni::Transform& tr, float deltaTime)
{
    if(puni::Input::IsKeyHeld(KEY_Y))
        tr.rotate(glm::vec3(0.0f,0.0f,1.0f), rotationSpeed * deltaTime);
    if(puni::Input::IsKeyHeld(KEY_B))
        tr.rotate(glm::vec3(0,0,1), -rotationSpeed * deltaTime);

    if(puni::Input::IsKeyPressed(KEY_X))
        movementSpeed = movementSpeed + 0.5f < 10 ? movementSpeed+0.5f : movementSpeed;
    else if(puni::Input::IsKeyPressed(KEY_B))
        movementSpeed = movementSpeed - 0.5f > 1 ? movementSpeed-0.5f : movementSpeed;
    
    if(puni::Input::IsKeyHeld(KEY_UP))
        tr.position += tr.Up() * movementSpeed * deltaTime;
    else if(puni::Input::IsKeyHeld(KEY_DOWN))
        tr.position -= tr.Up() * movementSpeed * deltaTime;

    if(puni::Input::IsKeyHeld(KEY_RIGHT))
        tr.position += tr.Right() * movementSpeed * deltaTime;
    else if(puni::Input::IsKeyHeld(KEY_LEFT))
        tr.position -= tr.Right() * movementSpeed * deltaTime;

    if(puni::Input::IsKeyHeld(KEY_ZL))
        tr.position += tr.Forward() * movementSpeed * deltaTime;
    else if(puni::Input::IsKeyHeld(KEY_ZR))
        tr.position -= tr.Forward() * movementSpeed * deltaTime;
}


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
    std::string vss = puni::loadTextFile(vertShaderPath);
    std::string fss = puni::loadTextFile(fragShaderPath);

    colourShader.compile(vertShaderPath, fragShaderPath);

    tri = PrimitiveShapes::CreateTriangle();

    faceImg.loadTexture(texturePath);

    vao = new puni::VertexArrayObject();

    puni::VertexAttributes vertAttribs[] = {
        {
            0, 3, GL_FLOAT, GL_FALSE, 
            sizeof(puni::Vertex), (void*)offsetof(puni::Vertex, puni::Vertex::pos)
        },
        {
            1, 3, GL_FLOAT, GL_FALSE, 
            sizeof(puni::Vertex), (void*)offsetof(puni::Vertex, puni::Vertex::col)
        },
        {
            2, 2, GL_FLOAT, GL_FALSE, 
            sizeof(puni::Vertex), (void*)offsetof(puni::Vertex, puni::Vertex::uv)
        }
    };

    
    vao->setupBuffers(tri.VertexBufferProperty().data(), tri.VertexBufferProperty().size());
    vao->setupAttributes(vertAttribs, 3);

    sceneCam.setAspectRatio(1280.0f,720.0f);
    sceneCam.setClippingPlanes(0.01f, 1000.0f);
    sceneCam.FieldOfView(45.0f);
    shaderTransfromLoc = glGetUniformLocation(colourShader.ID(), "transform");

    triTr.position = glm::vec3(0,0,-3);
    triTr.scale = glm::vec3(1);
    updateTransform(shaderTransfromLoc, sceneCam.ProjView() * triTr.TransformMat4());

    obj = &puni::Object::Instantiate<puni::Object>();
    testGO = puni::GameObject::Instantiate();
    testGO->name = "I'm alive!!!";
    testGO->AddComponent<puni::UpdateableComponent>();
    printf("GO info:\n%s\n\n", testGO->toString().c_str());

    glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

static void sceneRender()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    colourShader.use();
    faceImg.use();
    vao->bindVAO();
    updateTransform(shaderTransfromLoc, sceneCam.ProjView() * triTr.TransformMat4());
    glDrawElements(tri.MeshType(), tri.IndexCount(), GL_UNSIGNED_INT, 0);
}

static void sceneExit()
{
    puni::ObjectAllocator::Instance()->processDestroyQueue();
}

int main(int argc, char* argv[])
{
    // Set mesa configuration (useful for debugging)
    setMesaConfig();
    stbi_set_flip_vertically_on_load(true);
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
    puni::ComponentUpdateQueue* cpqueue = puni::ComponentUpdateQueue::Instance();
    // Main graphics loop    
    while (appletMainLoop())
    {
        // Get and process input
        puni::Input::RecordState();
        puni::Timer::Tick();

        if(puni::Input::IsKeyReleased(KEY_PLUS))
            break;

        if(puni::Input::IsKeyHeld(KEY_L | KEY_A))
        {
            printf("DeltaTime: %f\n\n", puni::Timer::DeltaTime());
        }
        else if(puni::Input::IsKeyPressed(KEY_R | KEY_A))
        {
            printf("ElapsedTime: %f\n\n", puni::Timer::ElapsedTime());
        }

        updateInput(triTr, puni::Timer::DeltaTime());
        cpqueue->updateComponents();
        // Render stuff!
        sceneRender();
        eglSwapBuffers(glInstance->Display(), glInstance->Surface());
    }

    //cleanup obj
    puni::GameObject copyObj = testGO;
    puni::GameObject::Destroy(copyObj);
    puni::ObjectAllocator::Instance()->addToDestroyQueue(obj);
    // Deinitialize our scene
    sceneExit();
    puni::ObjectAllocator::Instance()->processDestroyQueue();
    // Deinitialize EGL
    glInstance->DestroySelf();
    //deinitEgl();
    return EXIT_SUCCESS;
}
