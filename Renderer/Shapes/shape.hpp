#pragma once


#include <vector>
#include <string>
#include <array>
#include "../../glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../OpenGLUtils/opengl_program.hpp"


class Shape
{
public:
	virtual ~Shape() = 0 {};

	virtual void draw(OGLProgram& prog) = 0;
	virtual void bufferData(OGLProgram &prog, const std::string attrName) = 0;

	virtual void translate(const glm::vec3 vec) = 0;
	virtual void scale(const glm::vec3 vec) = 0;
	virtual void rotate(const glm::quat q) = 0;

	virtual void setColor(const glm::vec3 col) = 0;

protected:
	std::string name;
	glm::vec3 color;
};