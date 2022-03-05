#pragma once

#include <glm/glm.hpp>

class DiretionalLight
{
public:
	DiretionalLight() = default;
	//~DiretionalLight();

private:
	glm::vec3 direction;
	glm::vec3 ambientFactors;
	glm::vec3 diffuseFactors;
	glm::vec3 specularFactors;
};