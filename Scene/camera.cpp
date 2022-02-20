#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(const std::string name)
	:eye(glm::vec3(0.0f, 0.0f, -10.0f))
	,up(glm::vec3(0.0f, 1.0f, 0.0f))
	,gazePoint(glm::vec3(0.0f))
	,fovy(20.0f)
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
		return glm::perspective(fovy, aspectRatio, zNear, zFar);
	}
	
}

glm::mat4 Camera::getViewTransform()
{
	return glm::lookAt(eye, gazePoint, up);
}

void Camera::translate(const glm::vec3& move_dir)
{
}
