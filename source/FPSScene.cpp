#include "FPSScene.h"
#include "PrimitiveShapes.h"
#include <string>
#include <iostream>
#include "Input.h"
#include "Timer.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include <math.h>

void puni::FPSScene::cleanup()
{
    std::cout << "Cleaning up FPSScene.\n" << std::endl;
}

void puni::FPSScene::initialise()
{
    setupCamera();
    setupScene();
}

void puni::FPSScene::start()
{

}

void puni::FPSScene::update()
{
#ifndef __SWITCH__
    checkInput();
#endif
    checkController();
}

void puni::FPSScene::draw()
{
    grRenderer.draw(grTr);
    plRenderer.draw(plTr);
}

void puni::FPSScene::setupScene()
{
    //player vars
    movementSpeed = 10;
    rotationSpeed = 120;
    stickDeadZone = 0.1;
    sensitivity = 3;
    //material setup
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
#ifdef __SWITCH__
    std::string vertShaderPath = "romfs:/shaders/transform-coltex-shader.vs";
    std::string fragShaderPath = "romfs:/shaders/coltex-shader.fs";
    std::string plTexturePath = "romfs:/awesomeface.png";
    std::string grTexturePath = "romfs:/brick.jpg";
    auto modelPath = "romfs:/catbot.obj";
    auto modelTexturePath = "romfs:/catbot.png";
#elif __WINDOWS__
    std::string vertShaderPath = "romfs/shaders/transform-coltex-shader.vs";
    std::string fragShaderPath = "romfs/shaders/coltex-shader.fs";
    std::string plTexturePath = "romfs/catbot.png";
    std::string grTexturePath = "romfs/brick.jpg";
    auto modelPath = "romfs/catbot.obj";
    auto modelTexturePath = "romfs/catbot.png";
#endif
    playerMaterial = new Material();
    playerMaterial->loadShader(vertShaderPath, fragShaderPath);
    playerMaterial->setAttributes(vertAttribs, 3);
    playerMaterial->setTexture(new Texture(modelTexturePath));
    groundMaterial = new Material();
    groundMaterial->loadShader(vertShaderPath, fragShaderPath);
    groundMaterial->setAttributes(vertAttribs, 3);
    groundMaterial->setTexture(new Texture(grTexturePath));

    auto mesh = puni::Mesh::LoadFromOBJ(modelPath);
    //setup renderers
    plRenderer.setMesh(mesh);
    //plRenderer.setMesh(PrimitiveShapes::CreateCube());
    plRenderer.setMaterial(*playerMaterial);
    grRenderer.setMesh(PrimitiveShapes::CreateXZPlane());
    grRenderer.setMaterial(*groundMaterial);

    //setup transforms
    grTr.scale = glm::vec3(8.0f, 8.0f, 8.0f);
    plTr.position = glm::vec3(0.0f, 0.5f, 0.0f);
    plTr.scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void puni::FPSScene::checkInput()
{
    glm::vec3 moveDir = glm::vec3(0,0,0);
    if(Input::IsKeyHeld(GLFW_KEY_W))
        moveDir += plTr.Forward();
    else if(Input::IsKeyHeld(GLFW_KEY_S))
        moveDir -= plTr.Forward();
    if(Input::IsKeyHeld(GLFW_KEY_A))
        moveDir -= plTr.Right();
    else if(Input::IsKeyHeld(GLFW_KEY_D))
        moveDir += plTr.Right();

    if(glm::length2(moveDir) > 0.4f)
    {
        moveDir = glm::normalize(moveDir);
        plTr.position += moveDir * movementSpeed * Timer::DeltaTime();
    }
    // auto lJoy = Input::RawMouseMovementDelta();
    // bool move = false;
    // glm::vec3 moveDir = glm::vec3(0,0,0);
    // if(abs(lJoy.x) > stickDeadZone)
    // {
    //     move = true;
    //     moveDir += plTr.Right() * (float)lJoy.x;
    // }
    // if(abs(lJoy.y) > stickDeadZone)
    // {
    //     move = true;
    //     moveDir += plTr.Forward() * (float)lJoy.y;
    // }
    // if(move)
    // {
    //     if(glm::length2(moveDir) > stickDeadZone*stickDeadZone)
    //     {
    //         moveDir = glm::normalize(moveDir);
    //         plTr.position += moveDir * movementSpeed * Timer::DeltaTime();
    //     }
    // }
    // move = false;
    auto rJoy = Input::RawMouseMovementDelta();
    glm::vec3 angle = glm::vec3(0,-rJoy.x,0.0f);
    if(glm::length2(angle) > 0.1f)
    {
        angle = glm::normalize(angle);
        plTr.rotate(angle, sensitivity * rotationSpeed * Timer::DeltaTime());
    }
}

void puni::FPSScene::checkController()
{
    auto lJoy = Input::LeftAnalogAxes();
    bool move = false;
    glm::vec3 moveDir = glm::vec3(0,0,0);
    
    if(abs(lJoy.x) > stickDeadZone)
    {
        move = true;
        moveDir += plTr.Right() * (float)lJoy.x;
    }
    if(abs(lJoy.y) > stickDeadZone)
    {
        move = true;
        moveDir += plTr.Forward() * (float)lJoy.y;
    }
    if(move)
    {
        if(glm::length2(moveDir) > stickDeadZone*stickDeadZone)
        {
            moveDir = glm::normalize(moveDir);
            plTr.position += moveDir * movementSpeed * Timer::DeltaTime();
        }
    }
    move = false;
    auto rJoy = Input::RightAnalogAxes();
    glm::vec3 angle = glm::vec3(0,-rJoy.x,0.0f);
    if(glm::length2(angle) > 0.1f)
    {
        angle = glm::normalize(angle);
        plTr.rotate(angle, sensitivity * rotationSpeed * Timer::DeltaTime());
    }

    if(puni::Input::IsButtonPressed(GLFW_GAMEPAD_BUTTON_X))
        plTr.position = glm::vec3(0.0f, 0.5f, 0.0f);
}

void puni::FPSScene::setupCamera()
{
    sceneCam.setAspectRatio(1280.0f,720.0f);
    sceneCam.setClippingPlanes(0.01f, 1000.0f);
    sceneCam.FieldOfView(45.0f);
    sceneCam.transform.position = glm::vec3(0,8,15);
    sceneCam.transform.lookAt(glm::vec3(0));
    sceneCam.updateView();
}
