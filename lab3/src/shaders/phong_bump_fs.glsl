#version 330 core

in vec4 vpeye; // fragment position in eye coords

#define MAX_LIGHTS 32

uniform sampler2D the_texture;
uniform sampler2D normalmap;
uniform mat3 normalMatrix;

uniform float gamma = 2.2;
uniform int   lights_num;
uniform vec3  light_position[MAX_LIGHTS];
uniform vec3  diffuse_coef[MAX_LIGHTS];
uniform vec3  specular_coef[MAX_LIGHTS];
uniform float specular_exponent[MAX_LIGHTS];
uniform vec3  diffuse_color[MAX_LIGHTS];
uniform vec3  specular_color[MAX_LIGHTS];

in vec2 uv;

out vec4 fragmentColour;

void main() {

    vec3 c = texture(the_texture, uv).rgb / 4;
    fragmentColour.rgb = pow(c, vec3(gamma));

    vec3 n = 2 * texture(normalmap, uv).rgb - 1;
    vec4 vneye = vec4(normalMatrix * n, 0);

    for (int i = 0; i < lights_num; ++i) {
        vec4 n_eye = normalize(vneye);
        vec4 s_eye = normalize(vec4(light_position[i], 1) - vpeye);
        vec4 v_eye = normalize(-vpeye);
//        vec4 h_eye = normalize(v_eye + s_eye); // Blinn's half-way vector
        vec4 r_eye = reflect(-s_eye, vneye); // Phong's full reflection (could use instead of h)

        vec3 Id = diffuse_color[i] * diffuse_coef[i] * vec3(max(dot(s_eye, n_eye), 0.0));
        vec3 Is = specular_color[i] * specular_coef[i] * pow(max(dot(r_eye, v_eye), 0), specular_exponent[i]);

        float atten_factor = max (0.0, 1.0 - distance (vec3(vpeye), light_position[i]) / 10.0);

        fragmentColour.rgb +=  pow((Id + Is) * atten_factor, vec3(gamma));
    }
    fragmentColour.rgb = pow(fragmentColour.rgb, vec3(1 / gamma));
    fragmentColour.w = 1;
}