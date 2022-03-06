#include "rect.hpp"

#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Rect::Rect(const std::string name, const glm::vec3 o_scale, const glm::vec3 o_rotation, const glm::vec3 o_translation)
{
	this->name = name;
	color = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 l_translation_tabc = glm::vec3(-0.25f, -0.25f, 0.0f);
	glm::vec3 l_translation_tbdc = glm::vec3(0.25f, 0.25f, 0.0f);
	Triangle tabc(name + "_tabc", glm::vec3(1.0f), glm::vec3(0.0f), l_translation_tabc);
	Triangle tbdc(name + "_tbdc", glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, glm::radians(180.0f)), l_translation_tbdc);

	tabc.applyObjSpaceTransformations(o_scale, o_rotation, o_translation);
	tbdc.applyObjSpaceTransformations(o_scale, o_rotation, o_translation);
	triangles.push_back(tabc);
	triangles.push_back(tbdc);
}



Rect::~Rect()
{

}

void Rect::bufferData(OGLProgram& prog, const std::string attrName)
{
	for (auto& triangle : triangles)
	{
		triangle.bufferData(prog, attrName);
	}
}

void Rect::translate(const glm::vec3 vec)
{
	position += vec;
	for (auto& triangle : triangles)
	{
		triangle.translate(vec);
	}
}

void Rect::scale(const glm::vec3 vec)
{
	for (auto& triangle : triangles)
	{
		triangle.scale(vec);
	}
}

void Rect::rotate(const glm::quat q)
{
	for (auto& triangle : triangles)
	{
		triangle.rotate(q);
	}
}

void Rect::setColor(const glm::vec3 col)
{
	for(auto &triangle : triangles)
	{
		triangle.setColor(col);
	}
}

void Rect::draw(OGLProgram& prog)
{
	for (auto& triangle : triangles)
	{
		triangle.draw(prog);
	}
}
