#ifndef CAMERA__H_
#define CAMERA__H_

#include <glm\glm.hpp>
#include "Transform.h"

namespace puni
{
/** Camera Class Flag candidate
 * Might be good candidate for dirty flagging or flag monitoring
 * that way an update function can be made and just called every frame.
 * Performance monitoring is required to check if it makes a difference.
 * Till then, just keep in mind.
*/
	class Camera
	{
		public:
			Camera();
			~Camera();

			//probably should turn this into a function accessor to handle destruction cases
			static Camera* MainCamera;

			Transform transform;

			float FieldOfView() const;
			float AspectRatio() const;
			float NearPlane() const;
			float FarPlane() const;

			void FieldOfView(float degrees);

			glm::mat4 View() const;
			glm::mat4 Projection() const;
			glm::mat4 ProjView() const;

			void setAspectRatio(float width, float height);
			void setClippingPlanes(float near, float far);
			void updateProjection(); //called when changes are made to FOV, aspect, or clipping planes
			void updateView();

		private:
			glm::mat4 view, projection;
			float fov, aspect;
			float nearPlane;
			float farPlane;
	};
}
#endif