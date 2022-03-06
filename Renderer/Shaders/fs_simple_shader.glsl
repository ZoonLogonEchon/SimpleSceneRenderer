#version 460 core
in vec3 aFragPos;
in vec3 u_transformed_normal;
out vec4 FragColor;
#define MAX_NUM_POINT_LIGHTS 128
struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 u_obj_color;
uniform vec3 u_light_dir;
uniform vec3 u_camera_pos;

uniform PointLight u_point_lights[MAX_NUM_POINT_LIGHTS];
uniform int u_num_point_lights;

vec3 get_ambient_color(PointLight point_light)
{
    //float ambient_factor = 0.1;
	vec3 ambient_color = point_light.ambient * u_obj_color;
	return ambient_color;
}
vec3 get_diffuse_color(PointLight point_light, vec3 normal, vec3 light_dir)
{
	float diffuse_factor = max(dot(normal, light_dir), 0.0);
	vec3 diffuse_color = point_light.diffuse * diffuse_factor * u_obj_color;
	return diffuse_color;
}
vec3 get_spec_color(PointLight point_light, vec3 view_dir, vec3 reflect_dir)
{
	float shininess = 32.0;
	float spec_factor = pow(max(dot(view_dir, reflect_dir), 0.0), shininess);
	vec3 spec_color = point_light.specular * spec_factor * u_obj_color;
	return spec_color;
}
void main()
{
	vec3 normal = normalize(u_transformed_normal);
	vec3 view_dir = normalize(u_camera_pos - aFragPos);
	vec3 out_color = vec3(0.0, 0.0, 0.0);
	for (int i = 0; i < u_num_point_lights; ++i)
	{
		vec3 light_dir = normalize(u_point_lights[i].position - aFragPos);
		vec3 reflect_dir = reflect(-light_dir, normal);
		out_color = out_color + get_ambient_color(u_point_lights[i]);
		out_color = out_color + get_diffuse_color(u_point_lights[i], normal, light_dir);
		out_color = out_color + get_spec_color(u_point_lights[i], view_dir, reflect_dir);
	}
	FragColor = vec4(out_color, 1.0);
}