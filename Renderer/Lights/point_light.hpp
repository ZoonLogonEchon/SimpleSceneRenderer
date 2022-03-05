#pragma once
#include <string>
#include <glm/glm.hpp>

class PointLight
{
public:
	PointLight(const std::string name);
	//~PointLight();
	void translate(const glm::vec3 vec);
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
private:
	std::string name;
	
};