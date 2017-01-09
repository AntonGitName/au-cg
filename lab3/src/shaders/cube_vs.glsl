#version 330 core

uniform mat4 P, V;

layout(location = 0) in vec3 pos;
out vec3 direction;

void main () {
	gl_Position = P * V * vec4 (pos, 1.0);
	direction = pos;
}