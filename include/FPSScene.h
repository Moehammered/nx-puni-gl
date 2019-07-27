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
        FPSScene();
        ~FPSScene();

        void initialise() override;
        void start() override;
        void update() override;
        void draw() override;
        void cleanup() override;
        
    protected:
        void setupScene();
        void checkInput();
        void setupCamera();

        float           movementSpeed, rotationSpeed;
        double          stickDeadZone;
        Material        groundMaterial, playerMaterial;
        MeshRenderer    plRenderer, grRenderer;
        Transform       grTr, plTr;
    };
}

#endif
