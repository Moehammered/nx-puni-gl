#ifndef SWITCH__FPSMOVEMENTCOMPONENT__H_
#define SWITCH__FPSMOVEMENTCOMPONENT__H_

#include "UpdateableComponent.h"
#include <glm\glm.hpp>

namespace puni
{
	class FPSMovementComponent :
		public UpdateableComponent
	{
	public:
		FPSMovementComponent();
		~FPSMovementComponent();

		bool enablePitchRotation;
		float movementSpeed;
		float rotationSpeed;
		float mouseSensitivity;

		void initialise();
		void update() override;

	private:

		glm::vec3 movementDirection, rotationAxis;

		void checkPlayerMovement(Transform& tr, float deltaTime);
		// void checkPlayerRotation(Transform& tr, float deltaTime);
	};
}
#endif