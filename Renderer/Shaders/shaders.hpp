#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <string>
#include "shader_sources.hpp"
namespace Shaders {
	inline std::string getVertexShader() 
	{
		return std::string(VS_SIMPLE_SHADER_STRING);
	}
	inline std::string getFragmentShader()
	{
		return std::string(FS_SIMPLE_SHADER_STRING);
	}
	inline std::string getVertexNonShadingShader()
	{
		return std::string(VS_NON_SHADING_SHADER_STRING);
	}
	inline std::string getFragmentNonShadingShader()
	{
		return std::string(FS_NON_SHADING_SHADER_STRING);
	}
};
#endif // !SHADERS_HPP