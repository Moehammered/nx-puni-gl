#include "FPSMovementComponent.h"

#include "Input.h"
#include "Timer.h"
#define GLM_ENABLE_EXPERIMENTAL ///lets glm know we want experimental features
#include <glm\gtx\norm.hpp>
#include <switch.h>
#include "ComponentUpdateQueue.h"

puni::FPSMovementComponent::FPSMovementComponent()
{
	movementSpeed = rotationSpeed = mouseSensitivity = 1;
	enablePitchRotation = false;
	//printLine("FPSMOVECOMP");
}

puni::FPSMovementComponent::~FPSMovementComponent()
{
	printf("Destroy FPSMOVECOMP\n\n");
	printf("Removing from queue....\n");
	ComponentUpdateQueue::Instance()->removeFromQueue(id);
}

void puni::FPSMovementComponent::initialise()
{

}

void puni::FPSMovementComponent::update()
{
	checkPlayerMovement(owner->transform, Timer::DeltaTime());
	//checkPlayerRotation(owner->transform, Timer::DeltaTime());
}

void puni::FPSMovementComponent::checkPlayerMovement(Transform & tr, float deltaTime)
{
	movementDirection = glm::vec3(0);

	if (Input::IsKeyHeld(KEY_UP))
		movementDirection += tr.Forward();
	else if (Input::IsKeyHeld(KEY_DOWN))
		movementDirection -= tr.Forward();
	if (Input::IsKeyHeld(KEY_LEFT))
		movementDirection -= tr.Right();
	else if (Input::IsKeyHeld(KEY_RIGHT))
		movementDirection += tr.Right();

	if (glm::length2(movementDirection) > 0.4f)
	{
		movementDirection = glm::normalize(movementDirection);
		tr.position += movementDirection * movementSpeed * deltaTime;
	}
}

// void puni::FPSMovementComponent::checkPlayerRotation(Transform & tr, float deltaTime)
// {
// 	rotationAxis = glm::vec3(0);
// 	rotationAxis.y = -Input::RawMouseMovementDelta().x;

// 	if (glm::length2(rotationAxis) > 0.1f)
// 	{
// 		glm::vec3 finalAxis = glm::normalize(rotationAxis);
// 		tr.rotate(finalAxis, mouseSensitivity * rotationSpeed * deltaTime);
// 	}
// 	if (enablePitchRotation)
// 	{
// 		rotationAxis = glm::vec3(0);
// 		rotationAxis.x = Input::RawMouseMovementDelta().y;
// 		if (Input::IsKeyHeld(GLFW_KEY_UP))
// 			rotationAxis.x = 1;
// 		else if (Input::IsKeyHeld(GLFW_KEY_DOWN))
// 			rotationAxis.x = -1;

// 		if (glm::length2(rotationAxis) > 0.1f)
// 		{
// 			rotationAxis = glm::normalize(rotationAxis);
// 			tr.rotate(rotationAxis, rotationSpeed * deltaTime);
// 		}
// 	}
// }
