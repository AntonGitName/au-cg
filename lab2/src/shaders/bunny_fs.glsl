#version 330 core
precision highp float;

uniform samplerCube cube_texture;
uniform mat4 V;

in vec3 eye;
in vec3 normal;

out vec4 frag_color;

void main () {
	vec3 n_eye = normalize (eye);
	vec3 n_normal = normalize (normal);
	vec3 ray = reflect(n_eye, n_normal);
	ray = vec3 (inverse (V) * vec4 (ray, 0.0));

	frag_color = texture(cube_texture, ray);
}
