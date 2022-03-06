#include "point_light.hpp"
#include "../Shapes/cube.hpp"
PointLight::PointLight(const std::string name)
{
	this->name = name;
	position = glm::vec3(0.0f, 0.0f, -40.0f);
	ambient = glm::vec3(0.1f);
	diffuse = glm::vec3(1.0f);
	specular = glm::vec3(1.0f);
	shape = std::make_shared<Cube>("cube_" + name);
	shape->setColor(diffuse);
	shape->translate(position);
	shape->scale(glm::vec3(10.0f));
}

void PointLight::translate(const glm::vec3 vec)
{
	position += vec;
	shape->translate(vec);
}

void PointLight::bufferData(OGLProgram& program, const std::string attrName)
{
	shape->bufferData(program, attrName);
}

void PointLight::draw(OGLProgram& program)
{
	shape->draw(program);
}
