#version 460 core
in vec3 aFragPos;
out vec4 FragColor;
uniform vec3 u_normal;
uniform vec3 u_obj_color;
uniform vec3 u_light_dir;
uniform vec3 u_camera_pos;
vec3 get_ambient_color(vec3 light_color)
{
    float ambient_factor = 0.1;
	vec3 ambient_color = ambient_factor * light_color;
	return ambient_color;
}
vec3 get_diffuse_color(vec3 light_color, vec3 normal, vec3 light_dir)
{
	float diffuse_factor = max(dot(normal, light_dir), 0.0);
	vec3 diffuse_color = diffuse_factor * light_color;
	return diffuse_color;
}
vec3 get_spec_color(vec3 light_color, vec3 view_dir, vec3 reflect_dir)
{
	float spec_strength = 0.5;
	float spec_exp = 32.0;
	float spec_factor = pow(max(dot(view_dir, reflect_dir), 0.0), spec_exp);
	vec3 spec_color = spec_strength * spec_factor * light_color;
	return spec_color;
}
void main()
{
	vec3 light_color = vec3(1.0, 1.0, 1.0);
	vec3 normal = normalize(u_normal);
	vec3 view_dir = normalize(u_camera_pos - aFragPos);
	vec3 light_pos = vec3(0.0, 0.0, -10.0);
	vec3 light_dir = normalize(light_pos - aFragPos);
	vec3 reflect_dir = reflect(-light_dir, normal);
	vec3 out_color = vec3(0.0, 0.0, 0.0);
	out_color = out_color + get_ambient_color(light_color);
	out_color = out_color + get_diffuse_color(light_color, normal, light_dir);
	out_color = out_color + get_spec_color(light_color, view_dir, reflect_dir);
	out_color = out_color * u_obj_color; 
	FragColor = vec4(out_color, 1.0);
}