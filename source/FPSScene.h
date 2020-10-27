#ifndef SWITCH__FPSSCENE__H_
#define SWITCH__FPSSCENE__H_

#include "Scene.h"
#include "Material.h"
#include "MeshRenderer.h"

namespace puni
{
    class FPSScene : 
        public Scene
    {
    public:

        void initialise() override;
        void start() override;
        void update() override;
        void draw() override;
        void cleanup() override;
        
    protected:
        void setupScene();
        void checkInput();
        void checkController();
        void setupCamera();

        float           movementSpeed, rotationSpeed;
        float           sensitivity;
        double          stickDeadZone;
        //need to fix how deletion is handled so having value members works
        //if a material is copied then the member goes out of scope it will
        //destroy the shader. Either shaders are pre-compiled and referenced
        //then destroyed at the end when the framework cleans up
        //or the copying mechanism needs to be done differently.
        Material        *groundMaterial, *playerMaterial;
        MeshRenderer    plRenderer, grRenderer;
        Transform       grTr, plTr;
    };
}

#endif
