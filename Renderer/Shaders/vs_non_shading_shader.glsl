#version 460 core
in vec3 aPos;
out vec3 vsaPos;
uniform mat4 projection;
uniform mat4 view_transform;
uniform mat4 model_transform;
void main()
{
   mat4 pvm = projection * view_transform * model_transform;
   vsaPos = vec3( pvm * vec4(aPos, 1.0) );
   gl_Position = pvm * vec4(aPos, 1.0);
}