#version 330 core

layout(location = 0) in vec3 vp; // positions from mesh
layout(location = 1) in vec3 vn; // normals from mesh
uniform mat4 P, V, M; // proj, view, model matrices

void main () {
	gl_Position = P * V * M * vec4 (vp, 1.0);
}
