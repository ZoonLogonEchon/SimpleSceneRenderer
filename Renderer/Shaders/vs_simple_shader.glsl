#version 460 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aNormal;
out vec3 aFragPos;
out vec3 u_transformed_normal;
uniform mat4 projection;
uniform mat4 view_transform;
uniform mat4 model_transform;
uniform mat4 u_inv_model_transform;
void main()
{
   mat4 pvm = projection * view_transform * model_transform;
   //u_transformed_normal = mat3(transpose(u_inv_model_transform)) * aNormal;
   aFragPos = vec3(model_transform * vec4(aPos, 1.0));
   gl_Position = pvm * vec4(aPos, 1.0);
}