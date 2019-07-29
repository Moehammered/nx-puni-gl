#ifndef SWITCH__SCENE__H_
#define SWITCH__SCENE__H_

#include "Camera.h"

namespace puni
{
    class Scene
    {
    public:
        Scene();
        virtual ~Scene();

        virtual void initialise()=0;
        virtual void start()=0;
        virtual void update()=0;
        virtual void draw()=0;
        virtual void cleanup()=0;
        
    protected:
        Camera sceneCam;
    };
}

#endif