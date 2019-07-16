#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 col;
layout(location = 2) in vec2 uv;

out vec3 colour;
out vec2 texCoord;

uniform mat4 transform;

void main() {
  gl_Position = transform * vec4(vp, 1.0);
  colour = col;
  texCoord = uv;
}
