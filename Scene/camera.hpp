#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "../glad/glad.h"
#include <glm/glm.hpp>

class Camera {
public:
	enum class ProjectionType
	{
		Perspective,
		Orthographic
	};
	Camera() = default;
	Camera(const std::string name);
	~Camera();
	glm::mat4 getProjectionTransform(const float aspectRatio);
	glm::mat4 getProjectionTransform(const float width, const float height);
	glm::mat4 getViewTransform();
	// translates camera position keeping the same gaze direction
	void translate(const glm::vec3 &move_dir);
	void moveViewDir(const float movement_speed);
	void moveHorizontal(const float movement_speed);
	void moveVertical(const float movement_speed);
private:
	glm::vec3 eye;
	glm::vec3 gazePoint;
	glm::vec3 up;

	float fovy;
	float zNear;
	float zFar;
	ProjectionType projectionType;

	std::string name;
};