#include "scene.hpp"

Scene::Scene(const std::string name)
	:entitiesAmount(0)
{
	mainCamera = std::make_shared<SceneObject>(std::make_shared<EntityComponentsManager>(ecm), "MainCamera");;
	mainCamera->addComponent<Camera>();
	sceneObjects.push_back(mainCamera);
}

Scene::~Scene()
{
}

std::shared_ptr<SceneObject> Scene::addCube(const std::string name)
{
	auto test = std::make_shared<SceneObject>(std::make_shared<EntityComponentsManager>(ecm), name);
	test->addComponent<Mesh>();
	Mesh *comp = test->getComponent<Mesh>();
	*comp = Mesh(std::make_shared<Cube>());
	sceneObjects.push_back(test);
	return test;
}

std::shared_ptr<SceneObject> Scene::addTriangle(const std::string name)
{
	auto test = std::make_shared<SceneObject>(std::make_shared<EntityComponentsManager>(ecm), name);
	test->addComponent<Mesh>();
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

std::shared_ptr<SceneObject> Scene::addPointLight(const std::string name)
{
	auto test = std::make_shared<SceneObject>(std::make_shared<EntityComponentsManager>(ecm), name);
	test->addComponent<Mesh>();
	test->addComponent<PointLight>();
	Mesh* comp = test->getComponent<Mesh>();
	*comp = Mesh(std::make_shared<Cube>());
	sceneObjects.push_back(test);
	return test;
}


std::shared_ptr<SceneObject> Scene::addRect(const std::string name)
{
	//shapes.insert({ name, std::make_shared<Rect>(name) });
	auto test = std::make_shared<SceneObject>(std::make_shared<EntityComponentsManager>(ecm), name);
	test->addComponent<Mesh>();
	return test;
}

std::shared_ptr<SceneObject> Scene::getMainCamera()
{
	return mainCamera;
}

std::vector<std::shared_ptr<SceneObject>>& Scene::getSceneObjects()
{
	return sceneObjects;
}

