#pragma once
#include <string>
#include "shader_sources.hpp"
namespace Shaders {
	std::string getVertexShader() 
	{
		std::string src(VS_SIMPLE_SHADER_STRING);
		return src;
	}
	std::string getFragmentShader()
	{
		std::string src(FS_SIMPLE_SHADER_STRING);
		return src;
	}
};