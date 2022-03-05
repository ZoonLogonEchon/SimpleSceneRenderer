#include "point_light.hpp"

PointLight::PointLight(const std::string name)
{
	this->name = name;
	position = glm::vec3(0.0f, 0.0f, -40.0f);
	ambient = glm::vec3(0.1f);
	diffuse = glm::vec3(0.5f);
	specular = glm::vec3(1.0f);
}

void PointLight::translate(const glm::vec3 vec)
{
	position += vec;
}
