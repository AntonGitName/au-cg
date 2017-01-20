#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 2) in vec2 ts;

uniform mat4 modelViewMatrix;
uniform mat4 P;

out vec4 vpeye;

out vec2 uv;

void main() {
    uv = ts;
    vpeye = modelViewMatrix * vec4(pos, 1.0);
    gl_Position = P * modelViewMatrix * vec4(pos, 1.0);
}