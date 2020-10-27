#include "OpenGLLoader.h"
#include "Input.h"
#include <iostream>

// puni::Input* puni::Input::_instance = nullptr;
//std::vector<int> Input::prevKeyState;
//std::vector<int> Input::currKeyState;

std::vector<int> puni::Input::GetCurrKeyState()
{
    return Instance().currKeyState;
}

std::vector<int> puni::Input::GetPrevKeyState()
{
    return Instance().prevKeyState;
}

glm::vec2 & puni::Input::MousePosition()
{
	return Instance().mousePos;
}

glm::vec2 puni::Input::RawMouseMovementDelta()
{
	return Instance().mousePos - Instance().prevMousePos;
}

glm::vec2 puni::Input::NormalisedMouseMovementDelta()
{
	glm::vec2 raw = Input::RawMouseMovementDelta();

	raw.x /= (float)OpenGLLoader::Instance().ScreenWidth();
	raw.y /= (float)OpenGLLoader::Instance().ScreenHeight();

	return raw;
}

void puni::Input::Initialise()
{
	//Input in = Instance();
	#if INPUT_VERBOSEOUTPUT == 1
		std::cout << "init input" << std::endl;
	#endif
	Instance().prevKeyState.resize(GLFW_KEY_LAST + 1);
	Instance().currKeyState.resize(GLFW_KEY_LAST + 1);

	for(auto& btn : Instance().gamepadState.buttons)
		btn = 0;

	Instance().prevGamepadState = Instance().gamepadState;
}

void puni::Input::RecordGamepads()
{
	Input& in = Instance();
	in.prevGamepadState = in.gamepadState;
	glfwGetGamepadState(GLFW_JOYSTICK_1, &in.gamepadState);
	// #ifdef __SWITCH__
	// GLFWgamepadstate leftJoyCon;
	// glfwGetGamepadState(GLFW_JOYSTICK_2, &leftJoyCon);
	// in.gamepadState.axes[GLFW_GAMEPAD_AXIS_LEFT_X] = leftJoyCon.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
	// in.gamepadState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] = -leftJoyCon.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];;
	
	// #endif
}

bool puni::Input::IsButtonHeld(int btn)
{
	return Instance().gamepadState.buttons[btn] == GLFW_PRESS;
}

bool puni::Input::IsButtonPressed(int btn)
{
	Input& in = Instance();
	bool result = false;
	
	result = in.gamepadState.buttons[btn] == GLFW_PRESS;
	result = result && (in.prevGamepadState.buttons[btn] != GLFW_PRESS);

	return result;
}

bool puni::Input::IsButtonReleased(int btn)
{
	Input& in = Instance();
	bool result = false;

	result = in.gamepadState.buttons[btn] == GLFW_RELEASE;
	result = result && (in.prevGamepadState.buttons[btn] != GLFW_RELEASE);

	return result;
}

glm::vec2 puni::Input::LeftAnalogAxes()
{
	Input& in = Instance();
	glm::vec2 axes;
	axes.x = in.gamepadState.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
	axes.y = -in.gamepadState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
	return axes;
}

glm::vec2 puni::Input::RightAnalogAxes()
{
	Input& in = Instance();
	glm::vec2 axes;
	axes.x = in.gamepadState.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
	axes.y = -in.gamepadState.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];

	return axes;
}

glm::vec2 puni::Input::LeftAnalogAxesDelta()
{
	Input& in = Instance();
	glm::vec2 axes;
	axes.x = in.gamepadState.axes[GLFW_GAMEPAD_AXIS_LEFT_X] - in.prevGamepadState.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
	axes.y = -in.gamepadState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] + in.prevGamepadState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];

	return axes;
}

glm::vec2 puni::Input::RightAnalogAxesDelta()
{
	Input& in = Instance();
	glm::vec2 axes;
	axes.x = in.gamepadState.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] - in.prevGamepadState.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
	axes.y = -in.gamepadState.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] + in.prevGamepadState.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];

	return axes;
}

void puni::Input::RecordKeys()
{
	Input& in = Instance();
	for (size_t i = 0; i < in.prevKeyState.size(); ++i)
	{
		in.prevKeyState[i] = in.currKeyState[i];
	}
	//in.prevKeyState.assign(in.currKeyState.begin(), in.currKeyState.end());
}

void puni::Input::RecordMouseMovement()
{
	Input& in = Instance();
	double x, y;
	in.prevMousePos = in.mousePos;
	glfwGetCursorPos(OpenGLLoader::Instance().getWindow(), &x, &y);
	in.mousePos.x = x;
	in.mousePos.y = y;
}

void puni::Input::StoreKeyState(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	Input& in = Instance();
	//in.prevKeyState = in.currKeyState;
	if (key < 0)
		return;
	in.prevKeyState[key] = in.currKeyState[key];
	in.currKeyState[key] = action;
	#if INPUT_VERBOSEOUTPUT == 1
		std::cout << std::endl;
		std::cout << "Key(" << key << ") state(" << action << ")" << std::endl;
		std::cout << "CurrKey(" << key << ") Currstate(" << in.currKeyState[key] << ")" << std::endl;
		std::cout << "PrevKey(" << key << ") Prevstate(" << in.prevKeyState[key] << ")" << std::endl;
	#endif
}

bool puni::Input::IsKeyHeld(int key)
{
	return Instance().currKeyState[key] == GLFW_PRESS || Instance().currKeyState[key] == GLFW_REPEAT;
}

bool puni::Input::IsKeyPressed(int key)
{
	Input& in = Instance();
	bool result = false;
	
	result = in.currKeyState[key] == GLFW_PRESS;
	result = result && (in.prevKeyState[key] != GLFW_PRESS);

	return result;
}

bool puni::Input::IsKeyReleased(int key)
{
	Input& in = Instance();
	bool result = false;

	result = in.currKeyState[key] == GLFW_RELEASE;
	result = result && (in.prevKeyState[key] != GLFW_RELEASE);

	return result;
}

puni::Input::Input()
{
	/*prevKeyState.resize(GLFW_KEY_LAST + 1);
	currKeyState.resize(GLFW_KEY_LAST + 1);

	std::cout << "init input" << std::endl;*/
}

puni::Input & puni::Input::Instance()
{
	static Input instance;

	return instance;
}
