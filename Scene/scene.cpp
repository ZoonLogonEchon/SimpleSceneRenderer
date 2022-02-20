#include "scene.hpp"

Scene::Scene(const std::string name)
{
	cameras.insert({ "MainCamera", Camera("MainCamera") });
}

Scene::~Scene()
{
}

void Scene::addTriangle(const std::string name)
{
	triangles.insert({ name, Triangle(name) });
}

void Scene::addRect(const std::string name)
{
	rects.insert({name, Rect(name)});
}

std::unordered_map<std::string, Rect>& Scene::getAllRects()
{
	return rects;
}

std::unordered_map<std::string, Triangle>& Scene::getTriangles()
{
	return triangles;
}

Camera& Scene::getMainCamera()
{
	return cameras["MainCamera"];
}
