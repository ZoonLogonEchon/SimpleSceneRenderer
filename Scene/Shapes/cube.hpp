#pragma once

#include "../../glad/glad.h"
#include <vector>
#include <string>

#include "rect.hpp"


#include "../../Renderer/OGLProgram.hpp"

// cube built from rects (triangles would also be a possible implementation)
class Cube
{
public:
	Cube(const std::string name);
	~Cube();

	void draw(OGLProgram& prog);
	void bufferData(OGLProgram &prog, const std::string attrName);

	void translate(const glm::vec3 vec);
	void scale(const glm::vec3 vec);
	void rotate(const glm::quat q);

	std::string name;
	// although it's possi
	std::vector<Rect> rects;
	// rgb
	glm::vec3 color;
private:
	
};