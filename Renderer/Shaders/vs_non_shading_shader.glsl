#version 460 core
in vec3 aPos;
in vec3 aNormal;
out vec3 vsaPos;
out vec3 vsaNormal;
uniform mat4 projection;
uniform mat4 view_transform;
layout (std140) uniform u_pv
{
	mat4 p;
	mat4 v;
};
uniform mat4 model_transform;
uniform mat4 u_inv_model_transform;
void main()
{
   mat4 pvm = p * v * model_transform;
   vsaNormal = normalize(transpose(mat3(u_inv_model_transform)) * aNormal);
   vsaPos = vec3( pvm * vec4(aPos, 1.0) );
   gl_Position = pvm * vec4(aPos, 1.0);
}