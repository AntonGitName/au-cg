#version 330 core

uniform sampler2D tex;
in vec2 uv;
out vec4 frag_colour;

void main () {
	frag_colour = vec4 (texture (tex, uv).rgb, 1.0);
}