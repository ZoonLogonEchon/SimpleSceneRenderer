#pragma once
#include <string>
#include <glm/glm.hpp>
#include <memory>
class PointLight
{
public:
	PointLight()
		:ambient(glm::vec3(0.1f))
		,diffuse(glm::vec3(1.0f))
		,specular(glm::vec3(1.0f))
		,k_constant(1.0f)
		,k_linear(0.045f)
		,k_quadratic(0.0075f)
	{};
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::float32 k_constant;
	glm::float32 k_linear;
	glm::float32 k_quadratic;
};