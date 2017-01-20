#version 330 core

uniform sampler2D the_texture;
uniform sampler2D bump_exture;

in vec2 Texcoord;

out vec4 outColor;

void main() {
    outColor = texture(the_texture, Texcoord);
}