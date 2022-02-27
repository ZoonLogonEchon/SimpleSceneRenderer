#pragma once

#include "../../glad/glad.h"
#include <vector>

#include "../../Renderer/OGLProgram.hpp"

#include "triangle.hpp"

class Sphere
{
public:
	Sphere(const std::string name);
	~Sphere();

	void draw();
	void bufferData(OGLProgram& prog, const std::string attrName);
	unsigned int getPrimitivesCount();
	std::vector<Triangle> triangles;
	std::string name;
	// rgb
	glm::vec3 color;
private:
	
	
};