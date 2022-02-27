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
			"   mat4 pvm = projection * view_transform * model_transform;\n"
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
		"uniform vec3 u_normal;\n"
		"uniform vec3 u_obj_color;\n"
		"void main()\n"
		"{\n"
		"	vec3 light_color = vec3(1.0, 1.0, 1.0); \n"
		"	FragColor = vec4(u_obj_color, 1.0);\n"
		"}\0";
		return src;
	}
};