#include "scene.hpp"

Scene::Scene(const std::string name)
{
	cameras.insert({ "MainCamera", Camera("MainCamera") });
}

Scene::~Scene()
{
}

void Scene::addRect(const std::string name)
{
	rects.insert({name, Rect(name)});
}

std::unordered_map<std::string, Rect>& Scene::getAllRects()
{
	return rects;
}

Camera& Scene::getMainCamera()
{
	return cameras["MainCamera"];
}
