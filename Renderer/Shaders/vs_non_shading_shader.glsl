#version 460 core
layout (location = 1) in vec3 aPos;
uniform mat4 projection;
uniform mat4 view_transform;
uniform mat4 model_transform;
void main()
{
   mat4 pvm = projection * view_transform * model_transform;
   gl_Position = pvm * vec4(aPos, 1.0);
}