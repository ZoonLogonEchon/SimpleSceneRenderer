#include "scene.hpp"

Scene::Scene(const std::string name)
{
	mainCamera = SceneObject(std::make_shared<EntityComponentsManager>(ecm), "MainCamera");
	mainCamera.addComponent<Camera>();
	sceneObjects.push_back(mainCamera);
}

Scene::~Scene()
{
}

SceneObject& Scene::addCube(const std::string name)
{
	auto test = SceneObject(std::make_shared<EntityComponentsManager>(ecm), name);
	test.addComponent<Mesh>();
	*test.getComponent<Mesh>() = Cube(std::make_shared<MeshBuffer>());
	sceneObjects.push_back(test);
	return test;
}

SceneObject& Scene::addTriangle(const std::string name)
{
	auto test = SceneObject(std::make_shared<EntityComponentsManager>(ecm), name);
	test.addComponent<Mesh>();
	return test;
}

void Scene::translateShape(const std::string name, const glm::vec3 vec)
{
	//sceneObjects.at(name)->translate(vec);
}

void Scene::scaleShape(const std::string name, const glm::vec3 vec)
{
	//sceneObjects.at(name)->scale(vec);
}

void Scene::scaleShape(const std::string name, const float factor)
{
	//sceneObjects.at(name)->scale(glm::vec3(factor));
}

void Scene::rotateShape(const std::string name, const glm::vec3 angles)
{
	//sceneObjects.at(name)->rotate(glm::quat(angles));
}

void Scene::rotateShape(const std::string name, const glm::quat q)
{
	//sceneObjects.at(name)->rotate(q);
}

SceneObject& Scene::addPointLight(const std::string name)
{
	//pointLights.insert({ name, std::make_shared<PointLight>(name) });
	auto test = SceneObject(std::make_shared<EntityComponentsManager>(ecm), name);
	test.addComponent<PointLight>();
	test.addComponent<Mesh>();
	sceneObjects.push_back(test);
	return test;
}


SceneObject& Scene::addRect(const std::string name)
{
	//shapes.insert({ name, std::make_shared<Rect>(name) });
	auto test = SceneObject(std::make_shared<EntityComponentsManager>(ecm), name);
	test.addComponent<Mesh>();
	return test;
}

SceneObject& Scene::getMainCamera()
{
	return mainCamera;
}

std::vector<SceneObject>& Scene::getSceneObjects()
{
	return sceneObjects;
}

