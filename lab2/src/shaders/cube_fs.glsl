#version 330 core

uniform samplerCube cubemap;
in vec3 direction;
out vec4 color;

void main () {
	color = texture(cubemap, direction);
}