#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(const std::string name)
	:eye(glm::vec3(0.0f, 0.0f, 101.0f))
	,up(glm::vec3(0.0f, 1.0f, 0.0f))
	,gazePoint(glm::vec3(0.0f))
	,fovy(45.0f)
	,zNear(0.01f)
	,zFar(100.0f)
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

glm::mat4 Camera::getViewTransform()
{
	return glm::lookAt(eye, gazePoint, up);
}

void Camera::translate(const glm::vec3& move_dir)
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
