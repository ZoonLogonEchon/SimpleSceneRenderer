#include "scene.hpp"

Scene::Scene(const std::string name)
{
	cameras.insert({ "MainCamera", Camera("MainCamera") });
}

Scene::~Scene()
{
}

void Scene::addCube(const std::string name)
{
	shapes.insert({ name, std::make_shared<Cube>(name) });
}

void Scene::addTriangle(const std::string name)
{
	shapes.insert({ name, std::make_shared<Triangle>(name) });
}

void Scene::translateShape(const std::string name, const glm::vec3 vec)
{
	shapes.at(name)->translate(vec);
}

void Scene::scaleShape(const std::string name, const glm::vec3 vec)
{
	shapes.at(name)->scale(vec);
}

void Scene::scaleShape(const std::string name, const float factor)
{
	shapes.at(name)->scale(glm::vec3(factor));
}

void Scene::rotateShape(const std::string name, const glm::vec3 angles)
{
	shapes.at(name)->rotate(glm::quat(angles));
}

void Scene::rotateShape(const std::string name, const glm::quat q)
{
	shapes.at(name)->rotate(q);
}

void Scene::addPointLight(const std::string name)
{
	pointLights.insert({ name, std::make_shared<PointLight>(name) });
}

void Scene::addRect(const std::string name)
{
	shapes.insert({ name, std::make_shared<Rect>(name) });
}

void Scene::addSphere(const std::string name)
{
	//shapes.insert({ name, std::make_shared<Sphere>(name) });
}

std::unordered_map<std::string, std::shared_ptr<Shape>>& Scene::getShapes()
{
	return shapes;
}

Camera& Scene::getMainCamera()
{
	return cameras["MainCamera"];
}

std::unordered_map<std::string, std::shared_ptr<PointLight>> Scene::getPointLights()
{
	return pointLights;
}
