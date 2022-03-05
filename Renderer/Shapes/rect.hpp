#pragma once

#include "../../glad/glad.h"
#include <vector>
#include <string>
#include "shape.hpp"
#include "triangle.hpp"


#include "../OpenGLUtils/opengl_program.hpp"

class Rect : public Shape
{
public:
	Rect(const std::string name, const glm::vec3 o_scale = glm::vec3(1.0f), const glm::vec3 o_rotation = glm::vec3(0.0f), const glm::vec3 o_translation = glm::vec3(0.0f));
	~Rect() override;

	void draw(OGLProgram& prog) override;
	void bufferData(OGLProgram &prog, const std::string attrName) override;

	void translate(const glm::vec3 vec) override;
	void scale(const glm::vec3 vec) override;
	void rotate(const glm::quat q) override;
	void setColor(const glm::vec3 col) override;

	std::vector<Triangle> triangles;

private:
	
};