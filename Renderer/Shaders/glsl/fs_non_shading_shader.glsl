#version 460 core
in vec3 vsaPos;
in vec3 vsaNormal;
out vec4 FragColor;

void main()
{
	FragColor = vec4(vsaNormal, 1.0);
}