#version 330 core

uniform sampler2D the_texture;

in vec2 Texcoord;

out vec4 outColor;

void main() {
    outColor = texture(the_texture, Texcoord);
}