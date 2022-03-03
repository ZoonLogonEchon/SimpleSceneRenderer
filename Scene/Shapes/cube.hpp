#pragma once

#include "../../glad/glad.h"
#include <vector>
#include <string>

#include "rect.hpp"
#include "shape.hpp"

#include "../../Renderer/OGLProgram.hpp"

// cube built from rects (triangles would also be a possible implementation)
class Cube : public Shape
{
public:
	Cube(const std::string name);
	~Cube() override;

	void draw(OGLProgram& prog) override;
	void bufferData(OGLProgram &prog, const std::string attrName) override;

	void translate(const glm::vec3 vec) override;
	void scale(const glm::vec3 vec) override;
	void rotate(const glm::quat q) override;
	void setColor(const glm::vec3 col) override;

	std::vector<Rect> rects;
private:
	
};