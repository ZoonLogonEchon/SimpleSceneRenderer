#include "cube.hpp"

#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Cube::Cube(const std::string name)
{
	this->name = name;
	color = glm::vec3(1.0f, 0.0f, 0.0f);
	// front face
	Rect f1(name + "_ffront", glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.25f));
	f1.setColor(glm::vec3(1.0f, 0.0f, 0.0f)); // red
	// top face
	Rect f2(name + "_ftop", glm::vec3(1.0f), glm::vec3(glm::radians(-90.0f), 0.0f, 0.0f), glm::vec3(0.0f, 0.25f, 0.0f));
	f2.setColor(glm::vec3(0.0f, 1.0f, 0.0f)); // green
	// back face
	Rect f3(name + "_fback", glm::vec3(1.0f), glm::vec3(glm::radians(180.0f), 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -0.25f));
	f3.setColor(glm::vec3(0.0f, 0.0f, 1.0f)); // blue
	// bottom face
	Rect f4(name + "_fbottom", glm::vec3(1.0f), glm::vec3(glm::radians(90.0f), 0.0f, 0.0f), glm::vec3(0.0f, -0.25f, 0.0f));
	f4.setColor(glm::vec3(0.0f, 1.0f, 1.0f)); // turkis
	// left face
	Rect f5(name + "_fleft", glm::vec3(1.0f), glm::vec3(0.0f, glm::radians(90.0f), 0.0f), glm::vec3(-0.25f, 0.0f, 0.0f));
	f5.setColor(glm::vec3(1.0f, 1.0f, 0.0f)); // yellow
	// right face
	Rect f6(name + "_fleft", glm::vec3(1.0f), glm::vec3(0.0f, glm::radians(-90.0f), 0.0f), glm::vec3(0.25f, 0.0f, 0.0f));
	f6.setColor(glm::vec3(1.0f, 1.0f, 1.0f)); // white

	rects.push_back(f1);
	rects.push_back(f2);
	rects.push_back(f3);
	rects.push_back(f4);
	rects.push_back(f5);
	rects.push_back(f6);
}



Cube::~Cube()
{

}

void Cube::bufferData(OGLProgram& prog, const std::string attrName)
{
	for (auto& rect : rects)
	{
		rect.bufferData(prog, attrName);
	}
}

void Cube::translate(const glm::vec3 vec)
{
	position += vec;
	for (auto& rect : rects)
	{
		rect.translate(vec);
	}
}

void Cube::scale(const glm::vec3 vec)
{
	for (auto& rect : rects)
	{
		rect.scale(vec);
	}
}

void Cube::rotate(const glm::quat q)
{
	for (auto& rect : rects)
	{
		rect.rotate(q);
	}
}

void Cube::setColor(const glm::vec3 col)
{
	for (auto& rect : rects)
	{
		rect.setColor(col);
	}
}

void Cube::draw(OGLProgram& prog)
{
	for (auto& rect : rects)
	{
		rect.draw(prog);
	}
}
