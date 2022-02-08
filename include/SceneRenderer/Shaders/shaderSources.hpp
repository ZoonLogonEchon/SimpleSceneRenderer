#pragma once
#include <string>
namespace ShaderSources {
	std::string getVertexShader() 
	{
		std::string src =  
			"#version 460 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"uniform mat4 projection;\n"
			"uniform mat4 view_transform;\n"
			"uniform mat4 model_transform;\n"
			"void main()\n"
			"{\n"
			"   gl_PointSize = 5.0f;\n"
			"   mat4 pvm = projection * view_transform * model_transform ;\n"
			"   gl_Position = pvm * vec4(aPos, 1.0);\n"
			"}\0";
		return src;
	}
	std::string getParticleVertexShader()
	{
		std::string src =
			"#version 460 core\n"
			"layout (location = 1) in vec3 aPos;\n"
			"uniform vec4 normal;\n"
			"uniform mat4 projection;\n"
			"uniform mat4 view_transform;\n"
			"uniform mat4 model_transform;\n"
			"vec4 qMul(vec4 p, vec4 q)\n"
			"{\n"
			"	vec3 p_i = p.yzw;\n"
			"	vec3 q_i = q.yzw;\n"
			"	float res_r = (p.x * q.x - dot(p_i, q_i));\n"
			"   vec3 res_i = p.x * q_i + q.x * p_i + cross(p_i, q_i);\n"
			"   return vec4(res_r, res_i.x, res_i.y, res_i.z);\n"
			"}\n"
			"vec3 qRot(vec3 point, vec3 currOrientation, vec3 targetOrientation)\n"
			"{\n"
			"	float angle = dot(normalize(currOrientation), normalize(targetOrientation));\n"
			"	float s = sin(angle / 2.0);\n"
			"	float c = cos(angle / 2.0);\n"
			"	vec3 rotAxis = normalize(cross(currOrientation, targetOrientation));\n"
			"	vec4 q = vec4(c, s * rotAxis.x, s * rotAxis.y, s * rotAxis.z);\n"
			"	vec4 p = vec4(0.0, point.x, point.y, point.z);\n"
			"	vec4 q_1 = vec4(c, -s * rotAxis.x, -s * rotAxis.y, -s * rotAxis.z);\n"
			"	vec4 res = qMul(q, qMul(p, q_1));\n"
			"   return res.yzw;\n"
			"}\n"
			"void main()\n"
			"{\n"
			"   gl_PointSize = 5.0f;\n"
			"   //f_normal = normal;\n"
			"   mat4 pvm = projection * view_transform * model_transform ;\n"
			"   vec3 test = qRot(aPos, vec3(0.0, 0.0, -1.0), normal.xyz) ;\n"
			"   gl_Position = pvm * vec4(aPos, 1.0);\n"
			"}\0";
		return src;
	}
	std::string getFragmentShader()
	{
		std::string src = 
		"#version 460 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 vertex_color;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(vertex_color.xyz, 1.0);\n"
		"}\0";
		return src;
	}
	std::string getParticleFragmentShader()
	{
		std::string src =
			"#version 460 core\n"
			"uniform vec4 normal;\n"
			"out vec4 FragColor;\n"
			"uniform vec4 vertex_color;\n"
			"uniform float n_len_threshold;\n"
			"void main()\n"
			"{\n"
			"   vec4 test_color = vec4(vertex_color.xyz, 1);\n"
			"   if(length(normal) < n_len_threshold) {\n"
			"		test_color.w = mix(0.0, 0.7, length(normal) / n_len_threshold);\n"
			"   }\n"
			"	FragColor = test_color;\n"
			"}\0";
		return src;
	}
	std::string getGeometryShader()
	{
		std::string src = 
		"#version 460 core\n"
		"layout (points) in;\n"
		"layout (triangle_strip, max_vertices=4) out;\n"
		"in vec4 g_normal[];\n"
		"in mat4 g_pvm[];\n"
		"out vec4 f_normal;\n"
		"mat4 rotMatZ(float angle)\n"
		"{\n"
		"	float s = sin(angle);"
		"	float c = cos(angle);"
		"   return mat4(c, -s, 0.0, 0.0,"
		"				s, c, 0.0, 0.0,\n"
		"				0.0, 0.0, 1.0, 0.0,\n"
		"				0.0, 0.0, 0.0, 1.0);\n"
		"}\n"
		"mat4 rotMatY(float angle)\n"
		"{\n"
		"	float s = sin(angle);"
		"	float c = cos(angle);"
		"   return mat4(c, 0.0, s, 0.0,"
		"				0.0, 1.0, 0.0, 0.0,\n"
		"				-s, 0.0, c, 0.0,\n"
		"				0.0, 0.0, 0.0, 1.0);\n"
		"}\n"
		"mat4 rotMatX(float angle)\n"
		"{\n"
		"	float s = sin(angle);"
		"	float c = cos(angle);"
		"   return mat4(1.0, 0.0, 0.0, 0.0,"
		"				0.0, c, -s, 0.0,\n"
		"				0.0, s, c, 0.0,\n"
		"				0.0, 0.0, 0.0, 1.0);\n"
		"}\n"
		"void main()\n"
		"{\n"
		"   f_normal = g_normal[0];\n"
		"   vec4 axis_x = vec4(1.0, 0.0, 0.0, 0.0);\n"
		"   vec4 axis_y = vec4(0.0, 1.0, 0.0, 0.0);\n"
		"   vec4 axis_z = vec4(0.0, 0.0, 1.0, 0.0);\n"
		"   vec4 n_normal = normalize(g_normal[0]);\n"
		"   float angle_x = acos(dot(n_normal, axis_x));\n"
		"   float angle_y = acos(dot(n_normal, axis_y));\n"
		"   float angle_z = acos(dot(n_normal, axis_z));\n"
		"   mat4 rotMat = rotMatZ(angle_x) * rotMatY(angle_z) * rotMatX(angle_y);\n"
		"   float radius = 4.0f;\n"
		"   gl_Position = g_pvm[0] * (gl_in[0].gl_Position + (rotMat  * radius * vec4(0.1, 0.1, 0.0, 0.0)));\n"
		"   EmitVertex();\n"
		"   gl_Position = g_pvm[0] * (gl_in[0].gl_Position + (rotMat * radius * vec4(-0.1, 0.1, 0.0, 0.0)));\n"
		"   EmitVertex();\n"
		"   gl_Position = g_pvm[0] * (gl_in[0].gl_Position + (rotMat * radius * vec4(0.1, -0.1, 0.0, 0.0)));\n"
		"   EmitVertex();\n"
		"   gl_Position = g_pvm[0] * (gl_in[0].gl_Position + (rotMat * radius * vec4(-0.1, -0.1, 0.0, 0.0)));\n"
		"   EmitVertex();\n"
		"   EndPrimitive();\n"
		"}\n"
		"\0";
		return src;
	}
};