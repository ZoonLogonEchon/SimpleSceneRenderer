#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "../glad/glad.h"

#include "entity_components_manager.hpp"
#include "scene_object.hpp"
class Scene {
public:
	Scene(const std::string name);
	~Scene();

	SceneObject& addCube(const std::string name);
	SceneObject& addRect(const std::string name);
	SceneObject& addTriangle(const std::string name);
	SceneObject& addPointLight(const std::string name);

	void translateShape(const std::string name, const glm::vec3 vec);
	void scaleShape(const std::string name, const glm::vec3 vec);
	void scaleShape(const std::string name, const float factor);
	// rotation from euler angles (as radians)
	void rotateShape(const std::string name, const glm::vec3 angles);
	void rotateShape(const std::string name, const glm::quat q);

	SceneObject& getMainCamera();
	std::vector<SceneObject>& getSceneObjects();
private:
	EntityComponentsManager ecm;
	std::vector<SceneObject> sceneObjects;

	// scene obj with camera component
	SceneObject mainCamera;
};