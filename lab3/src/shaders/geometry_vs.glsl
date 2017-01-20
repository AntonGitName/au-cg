#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;

uniform mat4 P, V, M;

out vec3 p_eye;
out vec3 n_eye;

void main () {
  p_eye = vec3(V * M * vec4 (vp, 1.0));
  n_eye = vec3(V * M * vec4 (vn, 0.0));
  gl_Position = P * vec4 (p_eye, 1.0);
}