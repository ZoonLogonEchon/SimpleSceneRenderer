#pragma once
#include <string>
#include <glm/glm.hpp>
#include <memory>
class PointLight
{
public:
	PointLight() {};
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float k_constant;
	float k_linear;
	float k_quadratic;
};