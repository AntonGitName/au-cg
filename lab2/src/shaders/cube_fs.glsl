#version 330 core

//uniform samplerCube texture;
in vec3 uv;
out vec4 color;

void main () {
//	frag_colour = texture (texture, uv);
    color = v4(1 , 0, 0, 1);
}