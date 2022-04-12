#pragma once
#define VS_SIMPLE_SHADER_STRING "\
 #version 460 core\n\
 layout (location = 0) in vec3 aPos;\n\
 layout (location = 1) in vec3 aNormal;\n\
 out vec3 aFragPos;\n\
 out vec3 transformed_normal;\n\
 layout (std140) uniform u_pv\n\
 {\n\
 	mat4 projection;\n\
 	mat4 view_transform;\n\
 };\n\
 uniform mat4 model_transform;\n\
 uniform mat4 u_inv_model_transform;\n\
 void main()\n\
 {\n\
    mat4 pvm = projection * view_transform * model_transform;\n\
    transformed_normal = mat3(transpose(u_inv_model_transform)) * aNormal;\n\
    aFragPos = vec3(model_transform * vec4(aPos, 1.0));\n\
    gl_Position = pvm * vec4(aPos, 1.0);\n\
 }\n"
#define FS_SIMPLE_SHADER_STRING "\
 #version 460 core\n\
 in vec3 aFragPos;\n\
 in vec3 transformed_normal;\n\
 out vec4 FragColor;\n\
 #define MAX_NUM_POINT_LIGHTS 128\n\
 struct PointLight {\n\
 	vec3 position;\n\
 	vec3 ambient;\n\
 	vec3 diffuse;\n\
 	vec3 specular;\n\
 	float k_constant;\n\
 	float k_linear;\n\
 	float k_quadratic;\n\
 };\n\
 uniform vec3 u_obj_color;\n\
 uniform vec3 u_light_dir;\n\
 uniform vec3 u_camera_pos;\n\
 layout(std140) uniform u_lights\n\
 {\n\
 	int u_num_point_lights;\n\
 	PointLight u_point_lights[MAX_NUM_POINT_LIGHTS];\n\
 };\n\
 uniform PointLight u_point_lightss[MAX_NUM_POINT_LIGHTS];\n\
 uniform int u_num_point_lightss;\n\
 vec3 get_ambient_color(PointLight point_light)\n\
 {\n\
 	vec3 ambient_color = point_light.ambient * u_obj_color;\n\
 	return ambient_color;\n\
 }\n\
 vec3 get_diffuse_color(PointLight point_light, vec3 normal, vec3 light_dir)\n\
 {\n\
 	float diffuse_factor = max(dot(normal, light_dir), 0.0);\n\
 	vec3 diffuse_color = point_light.diffuse * diffuse_factor * u_obj_color;\n\
 	return diffuse_color;\n\
 }\n\
 vec3 get_spec_color(PointLight point_light, vec3 view_dir, vec3 reflect_dir)\n\
 {\n\
 	float shininess = 32.0;\n\
 	float spec_factor = pow(max(dot(view_dir, reflect_dir), 0.0), shininess);\n\
 	vec3 spec_color = point_light.specular * spec_factor * u_obj_color;\n\
 	return spec_color;\n\
 }\n\
 float calc_attenuation(PointLight point_light, float distance)\n\
 {\n\
 	return 1.0 / (point_light.k_constant + point_light.k_linear * distance + point_light.k_quadratic * (distance * distance));\n\
 }\n\
 void main()\n\
 {\n\
 	vec3 normal = normalize(transformed_normal);\n\
 	vec3 view_dir = normalize(u_camera_pos - aFragPos);\n\
 	vec3 out_color = vec3(0.0, 0.0, 0.0);\n\
 	for (int i = 0; i < u_num_point_lightss; ++i)\n\
 	{\n\
 		vec3 light_distance_vec = u_point_lightss[i].position - aFragPos;\n\
 		float distance = length(light_distance_vec);\n\
 		float attenuation = calc_attenuation(u_point_lightss[i], distance);\n\
 		vec3 light_dir = normalize(light_distance_vec);\n\
 		vec3 reflect_dir = reflect(-light_dir, normal);\n\
 		out_color = out_color + attenuation * get_ambient_color(u_point_lightss[i]);\n\
 		out_color = out_color + attenuation * get_diffuse_color(u_point_lightss[i], normal, light_dir);\n\
 		out_color = out_color + attenuation * get_spec_color(u_point_lightss[i], view_dir, reflect_dir);\n\
 		\n\
 	}\n\
 	out_color = transformed_normal + aFragPos + vec3(1.0);\n\
 	FragColor = vec4(out_color, 1.0);\n\
 }\n"

#define VS_NON_SHADING_SHADER_STRING "\
 #version 460 core\n\
 in vec3 aPos;\n\
 in vec3 aNormal;\n\
 out vec3 vsaPos;\n\
 out vec3 vsaNormal;\n\
 uniform mat4 projection;\n\
 uniform mat4 view_transform;\n\
 layout (std140) uniform u_pv\n\
 {\n\
 	mat4 p;\n\
 	mat4 v;\n\
 };\n\
 uniform mat4 model_transform;\n\
 uniform mat4 u_inv_model_transform;\n\
 void main()\n\
 {\n\
    mat4 pvm = p * v * model_transform;\n\
    vsaNormal = normalize(transpose(mat3(u_inv_model_transform)) * aNormal);\n\
    vsaPos = vec3( pvm * vec4(aPos, 1.0) );\n\
    gl_Position = pvm * vec4(aPos, 1.0);\n\
 }\n"
#define FS_NON_SHADING_SHADER_STRING "\
 #version 460 core\n\
 in vec3 vsaPos;\n\
 in vec3 vsaNormal;\n\
 out vec4 FragColor;\n\
 void main()\n\
 {\n\
 	FragColor = vec4(vsaNormal, 1.0);\n\
 }\n"
