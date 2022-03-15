#include "rect.hpp"

#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Rect::Rect()
{
	glm::vec3 l_translation_tabc = glm::vec3(-0.25f, -0.25f, 0.0f);
	glm::vec3 l_translation_tbdc = glm::vec3(0.25f, 0.25f, 0.0f);
	Triangle tabc;
	Triangle tbdc;
	tabc.applyObjSpaceTransformations(glm::vec3(1.0f), glm::vec3(0.0f), l_translation_tabc);
	tbdc.applyObjSpaceTransformations(glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, glm::radians(180.0f)), l_translation_tbdc);
	
	triangles.push_back(tabc);
	triangles.push_back(tbdc);
}

Rect::Rect(std::shared_ptr<MeshBuffer> mb)
	:Rect()
{
	meshBuffer = mb;
}

void Rect::applyObjSpaceTransformations(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation)
{
	for (auto& triangle : triangles)
	{
		triangle.applyObjSpaceTransformations(scale, rotation, translation);
	}
}

std::vector<float> Rect::getVertexData()
{
	std::vector<float> vertices;
	for (auto &triangle : triangles)
	{
		auto tr_verts = triangle.getVertexData();
		vertices.insert(vertices.end(), tr_verts.begin(), tr_verts.end());
	}
	return vertices;
}

std::vector<unsigned int> Rect::getFaceIndeces()
{
	std::vector<unsigned int> face_indeces;
	for (int k = 0; k < triangles.size(); ++k)
	{
		auto tr_f_indeces = triangles[k].getFaceIndeces();
		for (int i = 0; i < tr_f_indeces.size(); ++i)
		{
			face_indeces.push_back(tr_f_indeces[i] + k * tr_f_indeces.size());
		}
	}
	return face_indeces;
}



Rect::~Rect()
{

}

std::vector<float> Rect::getNormals()
{
	std::vector<float> normals;
	for (auto& triangle : triangles)
	{
		auto tr_verts = triangle.getNormals();
		normals.insert(normals.end(), tr_verts.begin(), tr_verts.end());
	}
	return normals;
}