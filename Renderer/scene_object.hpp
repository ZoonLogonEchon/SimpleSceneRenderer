#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>
#include <iostream>
#include "entity_components_manager.hpp"
#include "scene_object_components.hpp"
class SceneObject
{
public:
	// just to have a default ctor
	SceneObject() 
		:isCreated(false)
		,ecm(nullptr)
		,entity(-1)
		,name("!")
	{
		std::cout << "ctor dummy SceneObject " << name << std::endl;
	};

	SceneObject(std::shared_ptr<EntityComponentsManager> ecm, const std::string name)
		: isCreated(true)
	{

		this->ecm = ecm;	
		this->name = name;
		entity = ecm->createEntity();
		std::cout << "ctor SceneObject " << name << " --> " << entity << std::endl;
		ecm->addComponent<Transform>(entity);
	}

	SceneObject(const SceneObject& scene_object)
		: SceneObject()
	{
		
		isCreated = scene_object.isCreated;
		if (!isCreated)
		{
			return;
		}
		ecm = scene_object.ecm;
		entity = ecm->copyEntity(scene_object.entity);
		std::cout << "ctor copy SceneObject " << name << " copy from " << scene_object.name << ":" << std::to_string(scene_object.entity) << " --> " << entity << std::endl;
		name = scene_object.name;
	}

	SceneObject& operator=(const SceneObject& scene_object)
	{
		std::cout << "assign copy SceneObject " << name << " copy from " << scene_object.name << ":" << std::to_string(scene_object.entity) << std::endl;
		// clean this up
		if (isCreated)
		{
			ecm->removeEntity(entity);
			entity = -1;
			name = "!";
			ecm = nullptr;
		}
		isCreated = scene_object.isCreated;
		if (!isCreated)
		{
			return *this;
		}
		ecm = scene_object.ecm;
		entity = ecm->copyEntity(scene_object.entity);
		name = scene_object.name;
		return *this;
	}

	void moveTo(SceneObject& scene_object)
	{
		scene_object.entity = this->entity;
		scene_object.name = this->name;
		scene_object.ecm = this->ecm;
		scene_object.isCreated = this->isCreated;
	}

	~SceneObject()
	{
		std::cout << "dtor SceneObject " << name << ":" << std::to_string(entity) << std::endl;
		if(isCreated)
			ecm->removeEntity(entity);
		
	}

	template<class T>
	void addComponent()
	{
		if (isCreated)
			ecm->addComponent<T>(entity);
	}

	template<class T>
	T* getComponent()
	{
		if (!isCreated)
			return nullptr;

		return ecm->getComponent<T>(entity);
	}

private:
	bool isCreated;
	std::string name;
	EntityType entity;
	std::shared_ptr<EntityComponentsManager> ecm;
};