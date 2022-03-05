#pragma once

#include <glm/glm.hpp>

class DiretionalLight
{
public:
	DiretionalLight() = default;
	//~DiretionalLight();

private:
	glm::vec3 direction;
};