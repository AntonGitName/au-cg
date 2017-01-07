#version 330 core
layout(location = 0) in vec4 position_model;

uniform mat4 MVP;
uniform samplerBuffer TEXTURE;
uniform mat3 TRANSFORM;
uniform int FACTORIAL_ITERATIONS;
uniform vec2 DIMENSIONS;
out vec3 vColor;


void main() {
    float w = DIMENSIONS.x;
    float h = DIMENSIONS.y;
    float R2 = w * w + h * h;
    gl_Position =  MVP * position_model;

    vec3 pos = TRANSFORM * vec3(position_model) * vec3(DIMENSIONS, 1);
    float zx = 0;
    float zy = 0;
    int iteration = 0;

    for(; iteration < FACTORIAL_ITERATIONS; ++iteration) {
        float newzx = pos.x + zx * zx - zy * zy;
        zy = pos.y + 2 * zy * zx;
        zx = newzx;

        if (zx * zx + zy * zy > R2) {
            break;
        }
    }

    vColor = texelFetch(TEXTURE, iteration).rgb;
}