#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 2) in vec2 uv;

out vec2 Texcoord;

void main() {
    Texcoord = uv;
    gl_Position = vec4(pos, 1.0);
}