#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "../glad/glad.h"

#include "camera.hpp"
#include "Shapes/triangle.hpp"
#include "Shapes/rect.hpp"
#include "Shapes/sphere.hpp"

class Scene {
public:
	Scene(const std::string name);
	~Scene();

	void addRect(const std::string name);
	void translateRect(const std::string name, const glm::vec3 vec);
	void scaleRect(const std::string name, const glm::vec3 vec);
	void scaleRect(const std::string name, const float factor);
	// rotation from euler angles (as radians)
	void rotateRect(const std::string name, const glm::vec3 angles);
	void rotateRect(const std::string name, const glm::quat q);


	void addSphere(const std::string name);

	void addTriangle(const std::string name);
	void translateTriangle(const std::string name, const glm::vec3 vec);
	void scaleTriangle(const std::string name, const glm::vec3 vec);
	void scaleTriangle(const std::string name, const float factor);
	// rotation from euler angles (as radians)
	void rotateTriangle(const std::string name, const glm::vec3 angles);
	void rotateTriangle(const std::string name, const glm::quat q);


	std::unordered_map<std::string, Rect>& getRects();
	std::unordered_map<std::string, Sphere>& getSpheres();
	std::unordered_map<std::string, Triangle>& getTriangles();

	Camera &getMainCamera();
	// void toggleGlobalLight();
	// void setGlobalLight(glm::vec3 dir, glm::vec3 color);
private:
	std::unordered_map<std::string, Rect> rects;
	std::unordered_map<std::string, Sphere> spheres;
	std::unordered_map<std::string, Triangle> triangles;

	// including active camera
	std::unordered_map<std::string, Camera> cameras;
	// excluding global light
	// std::unorder_map<std::string, Light> lights;
	std::string nameActiveCamera;
};