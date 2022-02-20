#pragma once

#include "../../glad/glad.h"
#include <vector>

#include "../../Renderer/OGLProgram.hpp"

#include "triangle.hpp"

class Sphere
{
public:
	Sphere();
	~Sphere();

	void draw();
	void bufferData(OGLProgram& prog, const std::string attrName);
	unsigned int getPrimitivesCount();
private:
	std::vector<Triangle> triangles;
	
};