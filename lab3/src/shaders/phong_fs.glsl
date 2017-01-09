#version 330 core

in vec4 vpeye; // fragment position in eye coords
in vec4 vneye; // surface normal in eye coords

#define MAX_LIGHTS 16

uniform int lights_num; // light position in eye coords
uniform vec4 light_position[MAX_LIGHTS]; // light position in eye coords
uniform vec4 Ka[MAX_LIGHTS]; // ambient coefficient
uniform vec4 Kd[MAX_LIGHTS]; // diffuse coefficient
uniform vec4 Ks[MAX_LIGHTS]; // specular coefficient
uniform float Ns[MAX_LIGHTS]; // specular exponent
uniform vec4 Ld[MAX_LIGHTS]; // diffuse light colour

out vec4 fragmentColour;

void main() {

    fragmentColour = vec4(0.0, 0.0, 0.0, 0.0);

    for (int i = 0; i < lights_num; ++i) {
        vec4 n_eye = normalize(vneye); // normalise just to be on the safe side
        vec4 s_eye = normalize(light_position[i] - vpeye); // get direction from surface fragment to light
        vec4 v_eye = normalize(-vpeye); // get direction from surface fragment to camera
        vec4 h_eye = normalize(v_eye + s_eye); // Blinn's half-way vector
        //vec4 r_eye = reflect(-s_eye, vneye); // Phong's full reflection (could use instead of h)

        vec4 Ia = vec4(0.1,0.1,0.1,1) * Ka[i]; // ambient light has a hard-coded colour here, but we could load an La value
        vec4 Id = Ld[i] * Kd[i] * max(dot(s_eye, n_eye), 0.0); // max() is a safety catch to make sure we never get negative colours
        vec4 Is = vec4(1,1,1,1) * Ks[i] * pow(max(dot(h_eye, v_eye), 0), Ns[i]); // my ambient light colour is hard coded white, but could load Ls

        float atten_factor = max (0.0, 1.0 - distance (vpeye, light_position[i]) / 10.0);

        fragmentColour +=  (Ia + Id + Is) * atten_factor;
    }
}