#include <SceneRenderer/Shapes/rect.hpp>

#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Rect::Rect()
{
	unsigned i = 0;
	std::vector<float> a = {-0.5, 0.5, 0.0};
	std::vector<float> b =  {0.5, 0.5, 0.0};
	std::vector<float> c = {-0.5, -0.5, 0.0};
	std::vector<float> d =  {0.5, -0.5, 0.0};


	Triangle tabc({ a, b, c });
	Triangle tbcd({ b, c, d });

	triangles.push_back(tabc);
	triangles.push_back(tbcd);
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

void Rect::draw()
{
	for (auto& triangle : triangles)
	{
		triangle.draw();
	}
}
