#include "Transform.h"
#define GLM_ENABLE_EXPERIMENTAL ///lets glm know we want experimental features
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <iostream>

static std::string glm::Vec3ToString(glm::vec3 const& v3);

puni::Transform::Transform()
{
	position = glm::vec3(0);
	scale = glm::vec3(1);
	Rotation(glm::quat());
}


puni::Transform::~Transform()
{
}

const glm::quat puni::Transform::Rotation() const
{
	return rotation;
}

const glm::mat4 puni::Transform::RotationMat4() const
{
	return rotationMat4;
}

const glm::mat4 puni::Transform::TransformMat4() const
{
	glm::mat4 transformMat4;
	transformMat4 = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotMat = glm::mat4_cast(Rotation());
	transformMat4 = transformMat4 * rotMat; // right to left (rotate first, then move according to the transformMat4)
	transformMat4 = glm::scale(transformMat4, scale);

	return transformMat4;
}

glm::vec3 puni::Transform::Up()
{
	return up;
}

glm::vec3 puni::Transform::Forward()
{
	return forward;
}

glm::vec3 puni::Transform::Right()
{
	return right;
}

void puni::Transform::Rotation(glm::quat value)
{
	rotation = value;
	//working
	rotationMat4 = glm::mat4_cast(rotation);
	right = glm::vec3(rotationMat4[0][0], rotationMat4[0][1], rotationMat4[0][2]);
	up = glm::vec3(rotationMat4[1][0], rotationMat4[1][1], rotationMat4[1][2]);
	forward = -glm::normalize(glm::vec3(rotationMat4[2][0], rotationMat4[2][1], rotationMat4[2][2]));
}

void puni::Transform::translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}

void puni::Transform::translate(glm::vec3 delta)
{
	position += delta;
}

void puni::Transform::rotate(glm::vec3 axis, float angle)
{
	Rotation(rotation * glm::angleAxis(glm::radians(angle), axis));
}

//WORKS!!!! OMG THANK GOD!! --- https://stackoverflow.com/questions/18151845/converting-glmlookat-matrix-to-quaternion-and-back
void puni::Transform::lookAt(glm::vec3 target)
{
	glm::mat4 rot = glm::lookAt(position, target, up);
	Rotation(glm::conjugate(glm::toQuat(rot)));
}

std::string puni::Transform::toString()
{
	std::string st;

	st.append("Position: (");
	st.append(std::to_string(position.x));
	st.append(", ");
	st.append(std::to_string(position.y));
	st.append(",");
	st.append(std::to_string(position.z));
	st.append(")");

	st.append("\nForward: (");
	st.append(std::to_string(forward.x));
	st.append(", ");
	st.append(std::to_string(forward.y));
	st.append(",");
	st.append(std::to_string(forward.z));
	st.append(")");

	st.append("\nRight: ");
	st.append(glm::Vec3ToString(right));

	return st;
}


std::string glm::Vec3ToString(glm::vec3 const& v3)
{
	std::string st;

	st.append("(");
	st.append(std::to_string(v3.x));
	st.append(", ");
	st.append(std::to_string(v3.y));
	st.append(",");
	st.append(std::to_string(v3.z));
	st.append(")");

	return st;
}