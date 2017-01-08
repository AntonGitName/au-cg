#version 330 core
layout(location = 0) in vec4 position_model;

uniform mat4 MVP;
uniform samplerBuffer TEXTURE;
uniform mat3 TRANSFORM;
uniform int FACTORIAL_ITERATIONS;
uniform vec2 DIMENSIONS;
out vec3 color;


void main() {
    gl_Position =  MVP * position_model;

    vec3 pos = TRANSFORM * vec3(position_model) * vec3(DIMENSIONS, 0);
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