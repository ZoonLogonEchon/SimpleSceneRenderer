#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "../glad/glad.h"

#include "entity_components_manager.hpp"
#include "scene_object.hpp"
#include "config.hpp"
class Scene {
public:
	Scene(const std::string name);
	~Scene();

	std::shared_ptr<SceneObject> addCube(const std::string name);
	std::shared_ptr<SceneObject> addRect(const std::string name);
	std::shared_ptr<SceneObject> addTriangle(const std::string name);
	std::shared_ptr<SceneObject> addPointLight(const std::string name);

	void translateShape(const std::string name, const glm::vec3 vec);
	void scaleShape(const std::string name, const glm::vec3 vec);
	void scaleShape(const std::string name, const float factor);
	// rotation from euler angles (as radians)
	void rotateShape(const std::string name, const glm::vec3 angles);
	void rotateShape(const std::string name, const glm::quat q);

	std::shared_ptr<SceneObject> getMainCamera();
	std::vector<std::shared_ptr<SceneObject>>& getSceneObjects();
private:
	EntityComponentsManager ecm;
	std::vector<std::shared_ptr<SceneObject>> sceneObjects;
	size_t entitiesAmount;
	// scene obj with camera component
	std::shared_ptr<SceneObject> mainCamera;
};