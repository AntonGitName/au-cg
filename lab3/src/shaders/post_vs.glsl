#version 330 core

in vec3 vp;

out vec2 uv;

void main () {
	uv = vec2(vp);
	gl_Position = vec4(vp, 1.0);
}