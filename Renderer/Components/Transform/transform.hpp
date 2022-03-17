#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform {
public:
	Transform()
		:position(glm::vec3(0.0f))
		,orientation(1.0f, 0.0f, 0.0f, 0.0f)
		,size(1.0f)
	{}
	glm::mat4 getTransform()
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::scale(transform, size);
		transform = transform * glm::toMat4(orientation);
		return transform;
	};
	void translate(const glm::vec3 vec)
	{
		position += vec;
	};
	void scale(const glm::vec3 vec)
	{
		size *= vec;
	};
	void scale(const float factor)
	{
		scale(glm::vec3(factor));
	};
	void rotate(const glm::quat q)
	{
		orientation *= q;
	};
	void rotate(const glm::vec3 angles)
	{
		rotate(glm::quat(angles));
	};

	glm::vec3 position;
	glm::vec3 size;
	glm::quat orientation;
};