#pragma once
#ifdef TEST
#include "../../glad/glad.h"
#include <vector>

#include "../OpenGLUtils/opengl_program.hpp"

#include "triangle.hpp"

class Sphere
{
public:
	Sphere(const std::string name);
	~Sphere();

	void draw(OGLProgram& prog);
	void bufferData(OGLProgram& prog, const std::string attrName);
	unsigned int getPrimitivesCount();
	std::vector<Triangle> triangles;
	std::string name;
	// rgb
	glm::vec3 color;
private:
	
	
};
#endif