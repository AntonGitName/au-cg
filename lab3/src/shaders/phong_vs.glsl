#version 330 core

layout (location = 0) in vec3 vpos;
layout (location = 1) in vec3 vnorm;
layout (location = 2) in vec2 st;

uniform mat4 modelViewMatrix;
uniform mat4 P;
uniform mat3 normalMatrix;

out vec4 vpeye;
out vec4 vneye;
out vec2 uv;

void main() {
	uv = st;
	vpeye = modelViewMatrix * vec4(vpos, 1.0);
	vneye = vec4(normalMatrix * vnorm, 0);
	gl_Position = P * modelViewMatrix * vec4(vpos, 1.0);
}