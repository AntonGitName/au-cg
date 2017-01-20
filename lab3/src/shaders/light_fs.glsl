#version 330 core

uniform sampler2D p_tex;
uniform sampler2D n_tex;

uniform int screen_width;
uniform int screen_height;

uniform float gamma;

#define MAX_LIGHTS 32

uniform int lights_num;
uniform vec3 specular_color[MAX_LIGHTS];
uniform vec3 diffuse_color[MAX_LIGHTS];
uniform vec3 light_position[MAX_LIGHTS];
uniform vec3 diffuse_coef[MAX_LIGHTS];
uniform vec3 specular_coef[MAX_LIGHTS];
uniform float specular_exponent[MAX_LIGHTS];

out vec4 frag_colour;

vec3 phong(in vec3 op_eye, in vec3 n_eye) {

	vec3 res = vec3(0.0);

    for (int i = 0; i < lights_num; ++i) {
        vec3 lp_eye = light_position[i].xyz;
        vec3 dist_to_light_eye = lp_eye - op_eye;
        vec3 direction_to_light_eye = normalize (dist_to_light_eye);

        float dot_prod = max (dot (direction_to_light_eye,  n_eye), 0.0);
        vec3 Id = diffuse_color[i] * diffuse_coef[i] * dot_prod;


        vec3 reflection_eye = reflect (-direction_to_light_eye, n_eye);
        vec3 surface_to_viewer_eye = normalize (-op_eye);
        float dot_prod_specular = dot (reflection_eye, surface_to_viewer_eye);
        dot_prod_specular = max (dot_prod_specular, 0.0);
        float specular_factor = pow (dot_prod_specular, specular_exponent[i]);
        vec3 Is = specular_color[i] * specular_coef[i] * specular_factor;

        float dist_2d = max (0.0, 1.0 - distance (lp_eye, op_eye) / 10.0);
        float atten_factor =  dist_2d;

        res += (Id + Is) * atten_factor;
	}

	return res;
}

vec3 correction(in vec3 color) {
    return pow(color, vec3(1.0 / gamma));
}

void main () {
	frag_colour.a = 1.0;

	vec2 st;
	st.s = gl_FragCoord.x / screen_width;
	st.t = gl_FragCoord.y / screen_height;
	vec4 p_texel = texture (p_tex, st);

	// skip background
	if (p_texel.z > -0.0001) {
		discard;
	}

	vec4 n_texel = texture(n_tex, st);

	frag_colour.rgb = correction(phong(p_texel.rgb, normalize (n_texel.rgb)));
}