#pragma once
#include <string>
#include "shader_sources.hpp"
namespace Shaders {
	std::string getVertexShader() 
	{
		return std::string(VS_SIMPLE_SHADER_STRING);
	}
	std::string getFragmentShader()
	{
		return std::string(FS_SIMPLE_SHADER_STRING);
	}
	std::string getVertexNonShadingShader()
	{
		return std::string(VS_NON_SHADING_SHADER_STRING);
	}
	std::string getFragmentNonShadingShader()
	{
		return std::string(FS_NON_SHADING_SHADER_STRING);
	}
};