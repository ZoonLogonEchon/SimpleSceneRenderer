#pragma once

#include <vector>
#include <string>

#include "mesh.hpp"
#include "triangle.hpp"

class Rect : public Mesh
{
public:
	Rect();
	Rect(std::shared_ptr<MeshBuffer> mb);
	~Rect();
	std::vector<float> getVertexData() override;
	std::vector<unsigned int> getFaceIndeces() override;
	std::vector<float> getNormals() override;
	void applyObjSpaceTransformations(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation) override;
private:
	std::vector<Triangle> triangles;
};