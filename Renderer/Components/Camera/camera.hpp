#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>

class Camera {
public:
	enum class ProjectionType
	{
		Perspective,
		Orthographic
	};
	Camera();
	~Camera();
	glm::mat4 getProjectionTransform(const float aspectRatio);
	glm::mat4 getProjectionTransform(const float width, const float height);

	glm::vec3 lookDirection;
	glm::vec3 up;

	float fovy;
	float zNear;
	float zFar;
	ProjectionType projectionType;
};