#version 330 core

uniform samplerCube texture;
in vec3 uv;
out vec4 frag_colour;

void main () {
	frag_colour = texture (texture, uv);
}