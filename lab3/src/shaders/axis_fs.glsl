#version 330 core

in vec3 c;

out vec4 outColor;

void main() {
    outColor = vec4(c, 1);
}