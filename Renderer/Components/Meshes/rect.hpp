#pragma once

#include <vector>
#include <string>

#include "mesh_source.hpp"
#include "triangle.hpp"

class Rect : public MeshSource
{
public:
	Rect();
	~Rect();
	std::vector<float> getVertexData() override;
	std::vector<unsigned int> getFaceIndeces() override;
	std::vector<float> getNormals() override;
	VertexInfo getVertexInfo() override;
	unsigned int getVerticesAmount() override;
	void applyObjSpaceTransformations(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation) override;
private:
	std::vector<Triangle> triangles;
};