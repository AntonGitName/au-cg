#version 330


uniform vec3 sphere_color;

out vec4 frag_colour;

void main () {
	frag_colour = vec4(sphere_color, 1);
}
