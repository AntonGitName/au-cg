#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

uniform mat4 M, P, V;

out vec3 c;

void main() {
    c = color;
    gl_Position = P * V * M * vec4(pos, 1.0);
}