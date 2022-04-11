#pragma once

#include <bitset>
#include <chrono>
#include <memory>
#include "component_array.hpp"
#include "scene_object_components.hpp"
#include "config.hpp"
class EntityComponentsManager
{
private:
	template<class T>
	struct ComponentIndex
	{
		static const unsigned int index = MAX_ENTITIES + 1;
	};

	template<>
	struct ComponentIndex<PointLight> {
		static const unsigned int index = 0;
	};

	template<>
	struct ComponentIndex<Transform> {
		static const unsigned int index = 1;
	};

	template<>
	struct ComponentIndex<Mesh> {
		static const unsigned int index = 2;
	};
	template<>
	struct ComponentIndex<Camera> {
		static const unsigned int index = 3;
	};

public:
	EntityComponentsManager()
		:amountEntities(0)
	{
		componentsMatrix[ComponentIndex<PointLight>::index] = std::make_shared<ComponentArray<PointLight>>();
		componentsMatrix[ComponentIndex<Transform>::index] = std::make_shared<ComponentArray<Transform>>();
		componentsMatrix[ComponentIndex<Mesh>::index] = std::make_shared<ComponentArray<Mesh>>();
		componentsMatrix[ComponentIndex<Camera>::index] = std::make_shared<ComponentArray<Camera>>();
	}
	~EntityComponentsManager() {}
	EntityType createEntity()
	{
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		EntityType id = ms.count();
		entityEnabledComponents[id] = std::bitset<4>();
		++amountEntities;
		return id;
	}

	EntityType copyEntity(EntityType entity)
	{
		auto new_entity = createEntity();
		for (size_t i = 0; i < componentsMatrix.size(); i++)
		{
			if (componentsMatrix[i]->hasBinding(entity))
			{
				componentsMatrix[i]->createBinding(new_entity);
				componentsMatrix[i]->setBoundData(new_entity, componentsMatrix[i]->getBoundData(entity));
			}
				
		}
		return new_entity;
	}

	void removeEntity(EntityType entity)
	{
		for (size_t i = 0; i < componentsMatrix.size(); i++)
		{
			if (componentsMatrix[i]->hasBinding(entity))
				componentsMatrix[i]->removeBinding(entity);
		}
		entityEnabledComponents.erase(entity);
		--amountEntities;
	}

	template<class T>
	void addComponent(EntityType entity)
	{
		if (ComponentIndex<T>::index >= componentsMatrix.size())
		{
			std::cout << "unknown component type " << typeid(T).name() << std::endl;
			return;
		}
		componentsMatrix[ComponentIndex<T>::index]->createBinding(entity);
		entityEnabledComponents[entity][ComponentIndex<T>::index] = true;
	}

	template<class T>
	T* getComponent(EntityType entity)
	{

		if (ComponentIndex<T>::index >= componentsMatrix.size())
		{
			std::cout << "unknown component type " << typeid(T).name() << std::endl;
			return nullptr;
		}
		return reinterpret_cast<T*>(componentsMatrix[ComponentIndex<T>::index]->getBoundData(entity));
	}
private:
	std::array<std::shared_ptr<GeneralComponentArray>, 4> componentsMatrix;
	std::unordered_map<EntityType, std::bitset<4>> entityEnabledComponents;
	// observers
	std::unordered_map<std::string, unsigned int> systems;
	unsigned int amountEntities;
};
