#pragma once
#include <string>
#include <glm/glm.hpp>
#include <memory>
#include "../Shapes/shape.hpp"
class PointLight
{
public:
	PointLight(const std::string name);
	//~PointLight();
	void translate(const glm::vec3 vec);
	void bufferData(OGLProgram& program, const std::string attrName);
	void draw(OGLProgram& program);
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float k_constant;
	float k_linear;
	float k_quadratic;
private:
	std::string name;
	std::shared_ptr<Shape> shape;
};