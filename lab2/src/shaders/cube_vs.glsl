#version 330 core

uniform mat4 P, V;

layout(location = 0) in vec3 pos;
layout(location = 2) inout vec3 uv;

void main () {
	gl_Position = P * V * vec4 (pos, 1.0);
	uv = uv1;
}