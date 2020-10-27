#ifndef SWITCH__INPUT__H_
#define SWITCH__INPUT__H_

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

namespace puni
{
    class Input
    {
        public:
            static glm::vec2& MousePosition();
            static glm::vec2 RawMouseMovementDelta();
            static glm::vec2 NormalisedMouseMovementDelta();
            static void Initialise();
            static void RecordKeys();
            static void RecordMouseMovement();
            static void StoreKeyState(GLFWwindow* window, int key, int scancode,
                int action, int mods);

            static bool IsKeyHeld(int key);
            static bool IsKeyPressed(int key);
            static bool IsKeyReleased(int key);

            static void RecordGamepads();
            static void StoreJoystickState(GLFWwindow* window, int joystickID, int eventID);

            static bool IsButtonHeld(int btn);
            static bool IsButtonPressed(int btn);
            static bool IsButtonReleased(int btn);
            static glm::vec2 LeftAnalogAxes();
            static glm::vec2 RightAnalogAxes();
            static glm::vec2 LeftAnalogAxesDelta();
            static glm::vec2 RightAnalogAxesDelta();

            static std::vector<int> GetCurrKeyState();
            static std::vector<int> GetPrevKeyState();

        private:
            Input();

            static Input& Instance();

            std::vector<int> prevKeyState;
            std::vector<int> currKeyState;
            glm::vec2 mousePos, prevMousePos;

            GLFWgamepadstate prevGamepadState, gamepadState;
    };
}

#endif