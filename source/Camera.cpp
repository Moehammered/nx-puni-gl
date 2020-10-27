#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

puni::Camera* puni::Camera::MainCamera = nullptr;

puni::Camera::Camera()
{
	fov = glm::radians(45.0f);
	aspect = 800 / 600.0f;
	nearPlane = 0.1f;
	farPlane = 1000.0f;

	view = glm::lookAt(transform.position, transform.position + transform.Forward(), transform.Up());
	projection = glm::perspective(fov, aspect, nearPlane, farPlane);

	if (MainCamera == nullptr)
		MainCamera = this;
}

puni::Camera::~Camera()
{
}

float puni::Camera::FieldOfView() const
{
	return 0.0f;
}

float puni::Camera::AspectRatio() const
{
	return 0.0f;
}

float puni::Camera::NearPlane() const
{
	return 0.0f;
}

float puni::Camera::FarPlane() const
{
	return 0.0f;
}

void puni::Camera::FieldOfView(float degrees)
{
	fov = glm::radians(degrees);
	updateProjection();
}

glm::mat4 puni::Camera::View() const
{
	return view;
}

glm::mat4 puni::Camera::Projection() const
{
	return projection;
}

glm::mat4 puni::Camera::ProjView() const
{
	return projection * /*glm::inverse*/(view);
}

void puni::Camera::setAspectRatio(float width, float height)
{
	aspect = width / height;
	updateProjection();
}

void puni::Camera::setClippingPlanes(float near, float far)
{
	this->nearPlane = near;
	this->farPlane = far;
	updateProjection();
}

void puni::Camera::updateProjection()
{
	projection = glm::perspective(fov, aspect, nearPlane, farPlane);
}

void puni::Camera::updateView()
{
	glm::vec3 lookat = transform.position + transform.Forward();
	view = glm::lookAt(transform.position, lookat, transform.Up());
}
