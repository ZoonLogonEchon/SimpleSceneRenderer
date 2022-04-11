#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../../typedef.hpp"
class MeshSource 
{
public:
	virtual std::vector<float> getVertexData() = 0;
	virtual std::vector<unsigned int> getFaceIndeces() = 0;
	virtual std::vector<float> getNormals() = 0;
	virtual VertexInfo getVertexInfo() = 0;
	virtual unsigned int getVerticesAmount() = 0;
	virtual void applyObjSpaceTransformations(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation) = 0;
	
};