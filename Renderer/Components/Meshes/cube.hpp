#pragma once

#include <vector>
#include <string>

#include "rect.hpp"
#include "mesh_source.hpp"


// cube built from rects (triangles would also be a possible implementation)
class Cube : public MeshSource
{
public:
	Cube();
	~Cube();
	std::vector<float> getVertexData() override;
	std::vector<unsigned int> getFaceIndeces() override;
	std::vector<float> getNormals() override;
	VertexInfo getVertexInfo() override;
	unsigned int getVerticesAmount() override;
	void applyObjSpaceTransformations(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation) override;
private:
	std::vector<Rect> rects;
};