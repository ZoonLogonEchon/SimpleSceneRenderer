#include "cube.hpp"

#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Cube::Cube(const std::string name)
	:name(name)
	,color(glm::vec3(1.0f, 0.0f, 0.0f))
{
	unsigned i = 0;
	std::vector<float> a = {-0.5f, 0.5f, 0.0f};
	std::vector<float> b =  {0.5f, 0.5f, 0.0f};
	std::vector<float> c = {-0.5f, -0.5f, 0.0f};
	std::vector<float> d =  {0.5f, -0.5f, 0.0f};

	//they have to be added clockwise for the normals to be correct
	Triangle tabc(name + "_tabc", { a, b, c });
	Triangle tbcd(name + "_tbcd", { b, d, c });

	//triangles.push_back(tabc);
	//triangles.push_back(tbcd);
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

void Cube::draw(OGLProgram& prog)
{
	for (auto& rect : rects)
	{
		rect.draw(prog);
	}
}
