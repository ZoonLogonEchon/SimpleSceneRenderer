#version 460 core
out vec4 FragColor;

uniform vec3 u_obj_color;

void main()
{
	FragColor = vec4(u_obj_color, 1.0);
}