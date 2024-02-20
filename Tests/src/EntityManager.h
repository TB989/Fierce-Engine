#pragma once

#include "Types.h"
#include "Logger.h"

class EntityManager {
public:
	EntityManager(int maxEntities);
	~EntityManager();

	EntityId createEntity();
	void destroyEntity(EntityId entity);

private:
	int m_maxEntities;
	EntityId* entities;
	int pointer;
	Logger* logger;
};