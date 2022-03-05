#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "../glad/glad.h"

#include "camera.hpp"
#include "Shapes/triangle.hpp"
#include "Shapes/rect.hpp"
#include "Shapes/sphere.hpp"
#include "Shapes/cube.hpp"
#include "Shapes/shape.hpp"
class Scene {
public:
	Scene(const std::string name);
	~Scene();

	void addCube(const std::string name);

	void addRect(const std::string name);

	void addSphere(const std::string name);

	void addTriangle(const std::string name);

	void translateShape(const std::string name, const glm::vec3 vec);
	void scaleShape(const std::string name, const glm::vec3 vec);
	void scaleShape(const std::string name, const float factor);
	// rotation from euler angles (as radians)
	void rotateShape(const std::string name, const glm::vec3 angles);
	void rotateShape(const std::string name, const glm::quat q);


	std::unordered_map<std::string, std::shared_ptr<Shape>>& getShapes();

	Camera &getMainCamera();
	// void toggleGlobalLight();
	// void setGlobalLight(glm::vec3 dir, glm::vec3 color);
private:

	std::unordered_map<std::string, std::shared_ptr<Shape>> shapes;
	// including active camera
	std::unordered_map<std::string, Camera> cameras;
	// excluding global light
	// std::unorder_map<std::string, Light> lights;
	std::string nameActiveCamera;
};