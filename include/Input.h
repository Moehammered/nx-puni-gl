#ifndef SWITCH__INPUT__H_
#define SWITCH__INPUT__H_

#include <switch.h>

namespace puni
{
    class Input
    {
        public:
            static void Initialise();
            static void RecordState();
            static bool IsKeyHeld(unsigned int key);
            static bool IsKeyPressed(unsigned int key);
            static bool IsKeyReleased(unsigned int key);
            static JoystickPosition ReadLeftStick();
            static JoystickPosition ReadRightStick();

        private:
            Input();
            ~Input();
            
            static Input* _instance;

            static Input* const Instance();
    };
}

#endif