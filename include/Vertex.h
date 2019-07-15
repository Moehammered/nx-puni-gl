#ifndef SWITCH__VERTEX__H_
#define SWITCH__VERTEX__H_

#include <glm\vec3.hpp>
#include <glm\vec2.hpp>

namespace puni
{
    struct Vertex
    {
        public:
            glm::vec3 pos;
            glm::vec3 col;
            glm::vec2 uv;
    };
}

#endif