#include "cube.hpp"

#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Cube::Cube()
{
	// front face
	Rect f1;
	f1.applyObjSpaceTransformations(glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.25f));
	// top face
	Rect f2;
	f2.applyObjSpaceTransformations(glm::vec3(1.0f), glm::vec3(glm::radians(-90.0f), 0.0f, 0.0f), glm::vec3(0.0f, 0.25f, 0.0f));
	// back face
	Rect f3;
	f3.applyObjSpaceTransformations(glm::vec3(1.0f), glm::vec3(glm::radians(180.0f), 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -0.25f));
	// bottom face
	Rect f4;
	f4.applyObjSpaceTransformations(glm::vec3(1.0f), glm::vec3(glm::radians(90.0f), 0.0f, 0.0f), glm::vec3(0.0f, -0.25f, 0.0f));
	// left face
	Rect f5;
	f5.applyObjSpaceTransformations(glm::vec3(1.0f), glm::vec3(0.0f, glm::radians(90.0f), 0.0f), glm::vec3(-0.25f, 0.0f, 0.0f));
	// right face
	Rect f6;
	f6.applyObjSpaceTransformations(glm::vec3(1.0f), glm::vec3(0.0f, glm::radians(-90.0f), 0.0f), glm::vec3(0.25f, 0.0f, 0.0f));

	rects.push_back(f1);
	rects.push_back(f2);
	rects.push_back(f3);
	rects.push_back(f4);
	rects.push_back(f5);
	rects.push_back(f6);
}

Cube::Cube(std::shared_ptr<MeshBuffer> mb)
	:Cube()
{
	meshBuffer = mb;
}



Cube::~Cube()
{

}

void Cube::applyObjSpaceTransformations(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation)
{
}

std::vector<float> Cube::getVertexData()
{
	std::vector<float> vertices;
	for (auto& rect : rects)
	{
		auto rect_verts = rect.getVertexData();
		vertices.insert(vertices.end(), rect_verts.begin(), rect_verts.end());
	}
	return vertices;
}

std::vector<unsigned int> Cube::getFaceIndeces()
{
	std::vector<unsigned int> face_indeces;
	for (int k = 0; k < rects.size(); ++k)
	{
		auto tr_f_indeces = rects[k].getFaceIndeces();
		for (int i = 0; i < tr_f_indeces.size(); ++i)
		{
			face_indeces.push_back(tr_f_indeces[i] + k * tr_f_indeces.size());
		}
	}
	return face_indeces;
}

std::vector<float> Cube::getNormals()
{
	std::vector<float> normals;
	for (auto& rect : rects)
	{
		auto tr_verts = rect.getNormals();
		normals.insert(normals.end(), tr_verts.begin(), tr_verts.end());
	}
	return normals;
}