#version 330 core
layout(location = 0) in vec4 position_model;

uniform mat4 MVP;
uniform samplerBuffer TEXTURE;
uniform mat4 TRANSFORM;
uniform int FACTORIAL_ITERATIONS;
out vec3 color;


void main() {
    gl_Position =  MVP * position_model;

    vec4 pos = TRANSFORM * position_model;
    float zx = 0;
    float zy = 0;
    int iteration = 0;

    for(; iteration < FACTORIAL_ITERATIONS; ++iteration) {
        float newzx = pos.x + zx * zx - zy * zy;
        zy = pos.y + 2 * zy * zx;
        zx = newzx;

        if (zx * zx + zy * zy > 4) {
            break;
        }
    }

    color = texelFetch(TEXTURE, iteration).rgb;
}