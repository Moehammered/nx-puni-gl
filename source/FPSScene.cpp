#include "FPSScene.h"
#include "PrimitiveShapes.h"
#include <string>
#include <stdio.h>

puni::FPSScene::FPSScene() { }

puni::FPSScene::~FPSScene() { }

void puni::FPSScene::cleanup()
{
    printf("Cleaning up FPSScene.\n\n");
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
    rotationSpeed = 20;

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
    std::string vertShaderPath = "romfs:/shaders/transform-coltex-shader.vs";
    std::string fragShaderPath = "romfs:/shaders/coltex-shader.fs";
    std::string plTexturePath = "romfs:/awesomeface.png";
    std::string grTexturePath = "romfs:/brick.jpg";
    playerMaterial.loadShader(vertShaderPath, fragShaderPath);
    playerMaterial.setAttributes(vertAttribs, 3);
    playerMaterial.setTexture(new Texture(plTexturePath));
    groundMaterial.loadShader(vertShaderPath, fragShaderPath);
    groundMaterial.setAttributes(vertAttribs, 3);
    groundMaterial.setTexture(new Texture(grTexturePath));

    //setup renderers
    plRenderer.setMesh(PrimitiveShapes::CreateCube());
    plRenderer.setMaterial(playerMaterial);
    grRenderer.setMesh(PrimitiveShapes::CreateXZPlane());
    grRenderer.setMaterial(groundMaterial);

    //setup transforms
    grTr.scale = glm::vec3(8.0f, 8.0f, 8.0f);
    plTr.position = glm::vec3(0.0f, 0.5f, 0.0f);
    plTr.scale = glm::vec3(3.0f, 3.0f, 3.0f);
}

void puni::FPSScene::checkInput()
{

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
