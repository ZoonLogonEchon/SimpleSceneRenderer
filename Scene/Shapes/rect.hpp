#pragma once

#include "../../glad/glad.h"
#include <vector>
#include <string>

#include "triangle.hpp"


#include "../../Renderer/OGLProgram.hpp"

class Rect
{
public:
	Rect(const std::string name);
	~Rect();

	void draw();
	void bufferData(OGLProgram &prog, const std::string attrName);

	std::string name;
	std::vector<Triangle> triangles;
	// rgb
	glm::vec3 color;
private:
	
};