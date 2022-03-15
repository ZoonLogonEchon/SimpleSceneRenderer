#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "mesh.hpp"

class Triangle : public Mesh
{
public:
	Triangle();
	Triangle(std::shared_ptr<MeshBuffer> mb);
	~Triangle();
	std::vector<float> getVertexData() override;
	std::vector<unsigned int> getFaceIndeces() override;
	std::vector<float> getNormals() override;
	void applyObjSpaceTransformations(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation) override;
private:
	std::vector<float> vertices;
	std::vector<unsigned int> face_indeces;
	glm::vec3 normal;
	glm::vec3 objSpaceTransformations(glm::vec3 point, glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation);
	
};