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

	std::unordered_map<std::string, Rect>& getAllRects();

	Camera &getMainCamera();
private:
	std::unordered_map<std::string, Rect> rects;
	std::unordered_map<std::string, Sphere> spheres;
	std::unordered_map<std::string, Triangle> triangles;

	std::unordered_map<std::string, Camera> cameras;

	std::string nameActiveCamera;
};