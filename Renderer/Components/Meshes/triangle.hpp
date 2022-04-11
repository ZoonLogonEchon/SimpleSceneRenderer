#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "mesh_source.hpp"

class Triangle : public MeshSource
{
public:
	Triangle();
	~Triangle();
	std::vector<float> getVertexData() override;
	std::vector<unsigned int> getFaceIndeces() override;
	std::vector<float> getNormals() override;
	VertexInfo getVertexInfo() override;
	unsigned int getVerticesAmount() override;
	void applyObjSpaceTransformations(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation) override;
private:
	std::vector<float> vertices;
	std::vector<unsigned int> face_indeces;
	glm::vec3 normal;
	glm::vec3 objSpaceTransformations(glm::vec3 point, glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation);
	
};