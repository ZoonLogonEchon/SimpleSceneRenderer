#pragma once

#include <glm/glm.hpp>

class PointLight
{
public:
	PointLight() = default;
	//~PointLight();

private:
	glm::vec3 position;
};