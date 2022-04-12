#include "triangle.hpp"

#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Triangle::Triangle()
{

	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 top(0.0f, 0.5f, 0.0f);
	glm::vec3 right(0.5f, 0.0f, 0.0f);
	std::vector<float> t({
		center[0], center[1], center[2],  // center
		top[0], top[1], top[2],  // top
		right[0],  right[1], right[2]   // right
	});
	
	vertices = t;
	//applyObjSpaceTransformations(o_scale, o_rotation, o_translation);
	face_indeces = {  // note that we start from 0!
		0, 1, 2  // first triangle
	};
	
	center = glm::vec3(vertices[0], vertices[1], vertices[2]);
	top = glm::vec3(vertices[3], vertices[4], vertices[5]);
	right = glm::vec3(vertices[6], vertices[7], vertices[8]);
	glm::vec3 side_a = glm::normalize(top - center);
	glm::vec3 side_c = glm::normalize(right - center);
	normal = glm::normalize(glm::cross(side_c, side_a));

}

glm::vec3 Triangle::objSpaceTransformations(glm::vec3 point, glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation)
{
	glm::vec4 p(point, 1.0f);
	glm::quat q_rot(rotation);
	glm::vec4 s_p = glm::scale(glm::mat4(1.0f), scale) * p;
	glm::vec4 rs_p = glm::toMat4(q_rot) * s_p;
	glm::vec4 trs_p = glm::translate(glm::mat4(1.0f), translation) * rs_p;
	return glm::vec3(trs_p);
}

Triangle::~Triangle()
{
	
}


void Triangle::applyObjSpaceTransformations(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation)
{
	glm::vec3 center(vertices[0], vertices[1], vertices[2]);
	glm::vec3 top(vertices[3], vertices[4], vertices[5]);
	glm::vec3 right(vertices[6], vertices[7], vertices[8]);
	center = objSpaceTransformations(center, scale, rotation, translation);
	top = objSpaceTransformations(top, scale, rotation, translation);
	right = objSpaceTransformations(right, scale, rotation, translation);
	std::vector<float> t({
		center[0], center[1], center[2],  // center
		top[0], top[1], top[2],  // top
		right[0],  right[1], right[2]   // right
	});
	vertices = t;
	center = glm::vec3(vertices[0], vertices[1], vertices[2]);
	top = glm::vec3(vertices[3], vertices[4], vertices[5]);
	right = glm::vec3(vertices[6], vertices[7], vertices[8]);
	glm::vec3 side_a = glm::normalize(top - center);
	glm::vec3 side_c = glm::normalize(right - center);
	normal = glm::normalize(glm::cross(side_c, side_a));
}

std::vector<float> Triangle::getVertexData()
{
	std::vector<float> ret;
	for(int i = 0; i < getVerticesAmount(); ++i)
	{
		ret.push_back(vertices[i * getVerticesAmount()]);
		ret.push_back(vertices[i * getVerticesAmount() + 1]);
		ret.push_back(vertices[i * getVerticesAmount() + 2]);
		ret.push_back(normal[0]);
		ret.push_back(normal[1]);
		ret.push_back(normal[2]);
	}
	return ret;
}
std::vector<unsigned int> Triangle::getFaceIndeces()
{
	return face_indeces;
}

std::vector<float> Triangle::getNormals()
{
	return std::vector<float>({normal[0], normal[1], normal[2]});
}

VertexInfo Triangle::getVertexInfo()
{
	VertexInfo vi;
	vi.vertexSize = 3 * sizeof(decltype(vertices)::value_type) + 3 * sizeof(decltype(normal)::value_type);
	vi.attributeOffset["position"] = 0;
	vi.attributeOffset["normal"] = 3 * sizeof(decltype(vertices)::value_type);
	return vi;
}

unsigned int Triangle::getVerticesAmount()
{
	
	return 3;
}

