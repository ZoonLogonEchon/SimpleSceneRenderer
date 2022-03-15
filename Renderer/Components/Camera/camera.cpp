#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
Camera::Camera()
	:up(glm::vec3(0.0f, 1.0f, 0.0f))
	,lookDirection(glm::vec3(0.0f, 0.0f, -1.0f))
	,fovy(45.0f)
	,zNear(0.01f)
	,zFar(1000.0f)
	,projectionType(ProjectionType::Perspective)
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::getProjectionTransform(const float aspectRatio)
{
	if (projectionType == ProjectionType::Orthographic)
	{
		// TODO
		return glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, zNear, zFar);
	}
	else
	{
		return glm::perspective(glm::radians(fovy), aspectRatio, zNear, zFar);
	}
	
}

glm::mat4 Camera::getProjectionTransform(const float width, const float height)
{
	if (projectionType == ProjectionType::Orthographic)
	{
		return glm::ortho(-width/2.0f, width/2.0f, -height/2.0f, height/2.0f, zNear, zFar);
	}
	else
	{
		return glm::perspective(glm::radians(fovy), width / height, zNear, zFar);
	}
}

/*void Camera::translate(const glm::vec3& move_dir)
{
}

void Camera::moveViewDir(const float movement_speed)
{
	glm::vec3 view_dir = glm::normalize(gazePoint - eye);
	gazePoint += view_dir * movement_speed;
	eye += view_dir * movement_speed;
}

void Camera::moveHorizontal(const float movement_speed)
{
	glm::vec3 view_dir = glm::normalize(gazePoint - eye);
	gazePoint += glm::normalize(glm::cross(view_dir, up)) * movement_speed;
	eye += glm::normalize(glm::cross(view_dir, up)) * movement_speed;
}

void Camera::moveVertical(const float movement_speed)
{
	gazePoint += glm::normalize(up) * movement_speed;
	eye += glm::normalize(up) * movement_speed;
}

void Camera::lookAroundHorizontal(const float yaw)
{
	glm::vec3 view_vector = gazePoint - eye;
	float len = glm::length(view_vector);
	glm::vec3 view_dir = glm::normalize(view_vector);
	view_dir = glm::rotate(glm::mat4(1.0f), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(view_dir, 1.0f);
	gazePoint = eye + len * view_dir;
}*/
