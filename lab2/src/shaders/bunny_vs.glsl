#version 330 core

uniform mat4 P, V, M;

layout(location = 0) in vec3 local_pos;
layout(location = 1) in vec3 local_normal;

out vec3 eye;
out vec3 normal;

void main () {
	eye = vec3 (V * M * vec4 (local_pos, 1.0));
	normal = vec3 (V * M * vec4 (local_normal, 1.0));
	gl_Position = P * V * M * vec4 (local_pos, 1.0);
}
