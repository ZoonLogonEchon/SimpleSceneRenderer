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

void Scene::translateTriangle(const std::string name, const glm::vec3 vec)
{
	triangles.at(name).translate(vec);
}

void Scene::scaleTriangle(const std::string name, const glm::vec3 vec)
{
	triangles.at(name).scale(vec);
}

void Scene::scaleTriangle(const std::string name, const float factor)
{
	triangles.at(name).scale(glm::vec3(factor));
}

void Scene::rotateTriangle(const std::string name, const glm::vec3 angles)
{
	triangles.at(name).rotate(glm::quat(angles));
}

void Scene::rotateTriangle(const std::string name, const glm::quat q)
{
	triangles.at(name).rotate(q);
}

void Scene::addRect(const std::string name)
{
	rects.insert({ name, Rect(name) });
}

void Scene::addSphere(const std::string name)
{
	spheres.insert({ name, Sphere(name) });
}

std::unordered_map<std::string, Rect>& Scene::getRects()
{
	return rects;
}

std::unordered_map<std::string, Sphere>& Scene::getSpheres()
{
	return spheres;
}

std::unordered_map<std::string, Triangle>& Scene::getTriangles()
{
	return triangles;
}

Camera& Scene::getMainCamera()
{
	return cameras["MainCamera"];
}
