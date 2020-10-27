#ifndef SWITCH__GLMHELPERS__H_
#define SWITCH__GLMHELPERS__H_

#include <glm/vec3.hpp>
#include <string>

///expand functionality of glm in here
namespace glm
{
	std::string Vec3ToString(glm::vec3 const& v3);
}

#endif