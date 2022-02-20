#include "sphere.hpp"
#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Sphere::Sphere()
{
	unsigned i = 0;
	std::pair<std::vector<float>, unsigned> a = { {0.0, 0.5, 0.0}, i++ };
	std::pair<std::vector<float>, unsigned> b = { {0.0, -0.5, 0.0}, i++ };
	std::pair<std::vector<float>, unsigned> c = { {0.5, 0.0, 0.0}, i++ };
	std::pair<std::vector<float>, unsigned> d = { {-0.5, 0.0, 0.0}, i++ };
	std::pair<std::vector<float>, unsigned> e = { {0.0, 0.0, 0.5}, i++ };
	std::pair<std::vector<float>, unsigned> f = { {0.0, 0.0, -0.5}, i++ };


	Triangle tade({ a.first, d.first, e.first });
	Triangle tace({ a.first, c.first, e.first });
	Triangle tacf({ a.first, c.first, f.first });
	Triangle tadf({ a.first, d.first, f.first });
	Triangle tbde({ b.first, d.first, e.first });
	Triangle tbce({ b.first, c.first, e.first });
	Triangle tbcf({ b.first, c.first, f.first });
	Triangle tbdf({ b.first, d.first, f.first });

	triangles.push_back(tade);
	triangles.push_back(tace);
	triangles.push_back(tacf);
	triangles.push_back(tadf);
	triangles.push_back(tbde);
	triangles.push_back(tbce);
	triangles.push_back(tbcf);
	triangles.push_back(tbdf);
}

Sphere::~Sphere()
{

}

unsigned int Sphere::getPrimitivesCount()
{
	return triangles.size();
}

void Sphere::bufferData(OGLProgram& prog, const std::string attrName)
{
	//triangles[index].bufferData();
	for(auto &triangle : triangles)
	{
		triangle.bufferData(prog, attrName);
	}
}

void Sphere::draw()
{

	for (auto& triangle : triangles)
	{
		triangle.draw();
	}
	
}
