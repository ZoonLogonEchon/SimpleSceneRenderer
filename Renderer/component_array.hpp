#pragma once

#include <array>
#include <unordered_map>
#include <iostream>
#include <string>
#include "config.hpp"
#include "typedef.hpp"

class GeneralComponentArray
{
public:
	virtual void createBinding(EntityType) = 0;
	virtual void removeBinding(EntityType) = 0;
	virtual void* getBoundData(EntityType) = 0;
	virtual bool hasBinding(EntityType) = 0;
	virtual void setBoundData(EntityType entity, void* data) = 0 ;
};

template<class T>
class ComponentArray : public GeneralComponentArray
{
public:
	void createBinding(EntityType entity) override
	{
		if (hasBinding(entity))
		{
			std::cout << "createBinding: entity " << std::to_string(entity) << " has already Component of type " << typeid(T).name() << std::endl;
			return;
		}
		std::cout << "createBinding: entity " << std::to_string(entity) << " type " << typeid(T).name() << std::endl;
		components[currentSize] = T();
		entityComponentBindings[entity] = currentSize;
		componentEntityBindings[currentSize] = entity;
		++currentSize;
	}

	void removeBinding(EntityType entity) override
	{
		if (!hasBinding(entity))
		{
			std::cout << "removeBinding: entity " << std::to_string(entity) << " didn't have a Component of type " << typeid(T).name() << std::endl;
			return;
		}
		std::cout << "removeBinding: entity " << std::to_string(entity) << " type " << typeid(T).name() << std::endl;
		auto component_rm_index = entityComponentBindings[entity];
		auto component_last_index = currentSize - 1;
		components[component_rm_index] = components[component_last_index];

		auto entity_last = componentEntityBindings[component_last_index];
		entityComponentBindings[entity_last] = component_rm_index;
		componentEntityBindings[component_rm_index] = entity_last;

		entityComponentBindings.erase(entity);
		componentEntityBindings.erase(component_last_index);

		--currentSize;
	}

	bool hasBinding(EntityType entity) override
	{
		return (entityComponentBindings.find(entity) != entityComponentBindings.end());
	}

	void* getBoundData(EntityType entity) override
	{
		if (!hasBinding(entity))
		{
			std::cout << "getBoundData: entity " << std::to_string(entity) << " didn't have a Component of type " << typeid(T).name() << std::endl;
			return nullptr;
		}
		auto index = entityComponentBindings[entity];
		return reinterpret_cast<void *>(&components[index]);
	}

	void setBoundData(EntityType entity, void* data) override
	{
		if (!hasBinding(entity))
		{
			std::cout << "getBoundData: entity " << std::to_string(entity) << " didn't have a Component of type " << typeid(T).name() << std::endl;
			return;
		}
		T* typed_data = reinterpret_cast<T*>(data);
		auto index = entityComponentBindings[entity];
		components[index] = *typed_data;
	}

private:
	unsigned int currentSize = 0;
	std::array<T, MAX_ENTITIES> components;
	std::unordered_map<EntityType, unsigned int> entityComponentBindings;
	std::unordered_map<unsigned int, EntityType> componentEntityBindings;
};