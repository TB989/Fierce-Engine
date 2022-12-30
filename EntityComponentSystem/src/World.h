#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"

#include <vector>

using Entity = int;

class World {
public:
	World();
	~World();

	//ECS
	Entity createEntity() { return entityManager->createEntity(); }
	void destroyEntity(Entity entity) { entityManager->destroyEntity(entity); }

	template<typename T>
	void addComponent(Entity entity, T component) { componentManager->addComponent<T>(entity, component); }

	template<typename T>
	void removeComponent(Entity entity) { componentManager->removeComponent<T>(entity); }

	template<typename T>
	T& getComponent(Entity entity) { return componentManager->getComponent<T>(entity); }

private:
	EntityManager* entityManager;
	ComponentManager* componentManager;
};