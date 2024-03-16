#include "EntityManager.h"

EntityManager::EntityManager(int maxEntities){
	m_maxEntities = maxEntities;
	pointer = 0;
	entities = new EntityId[maxEntities];
	logger = new Logger("ECS");

	for (int i = 0; i < maxEntities; i++) {
		entities[i] = i;
	}
}

EntityManager::~EntityManager() {
	if (pointer != 0) {
		logger->warn("%d entities have not been destroyed",pointer);
	}
	delete[] entities;
}

EntityId EntityManager::createEntity() {
	EntityId entity= entities[pointer];
	pointer++;
	return entity;
}

void EntityManager::destroyEntity(EntityId entity) {
	pointer--;
	entities[pointer] = entity;
}