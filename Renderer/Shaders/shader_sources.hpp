#pragma once
#define VS_SIMPLE_SHADER_STRING "\
 #version 460 core\n\
 layout (location = 0) in vec3 aPos;\n\
 out vec3 aFragPos;\n\
 uniform mat4 projection;\n\
 uniform mat4 view_transform;\n\
 uniform mat4 model_transform;\n\
 uniform mat4 u_inv_model_transform;\n\
 void main()\n\
 {\n\
    mat4 pvm = projection * view_transform * model_transform;\n\
    aFragPos = vec3(model_transform * vec4(aPos, 1.0));\n\
    gl_Position = pvm * vec4(aPos, 1.0);\n\
 }\n"
#define FS_SIMPLE_SHADER_STRING "\
 #version 460 core\n\
 in vec3 aFragPos;\n\
 out vec4 FragColor;\n\
 #define MAX_NUM_POINT_LIGHTS 128\n\
 struct PointLight {\n\
 	vec3 position;\n\
 	vec3 ambient;\n\
 	vec3 diffuse;\n\
 	vec3 specular;\n\
 };\n\
 uniform vec3 u_normal;\n\
 uniform vec3 u_obj_color;\n\
 uniform vec3 u_light_dir;\n\
 uniform vec3 u_camera_pos;\n\
 uniform PointLight u_point_lights[MAX_NUM_POINT_LIGHTS];\n\
 uniform int u_num_point_lights;\n\
 vec3 get_ambient_color(PointLight point_light)\n\
 {\n\
     //float ambient_factor = 0.1;\n\
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
 void main()\n\
 {\n\
 	vec3 normal = normalize(u_normal);\n\
 	vec3 view_dir = normalize(u_camera_pos - aFragPos);\n\
 	vec3 out_color = vec3(0.0, 0.0, 0.0);\n\
 	for (int i = 0; i < u_num_point_lights; ++i)\n\
 	{\n\
 		vec3 light_dir = normalize(u_point_lights[i].position - aFragPos);\n\
 		vec3 reflect_dir = reflect(-light_dir, normal);\n\
 		out_color = out_color + get_ambient_color(u_point_lights[i]);\n\
 		out_color = out_color + get_diffuse_color(u_point_lights[i], normal, light_dir);\n\
 		out_color = out_color + get_spec_color(u_point_lights[i], view_dir, reflect_dir);\n\
 	}\n\
 	FragColor = vec4(out_color, 1.0);\n\
 }\n"
