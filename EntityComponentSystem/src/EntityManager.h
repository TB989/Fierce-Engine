#pragma once

#include "utils/Logging.h"

using Entity = int;

class EntityManager{
public:
	EntityManager(int maxEntities) {
		m_maxEntities = maxEntities;
		entityIDs = new Entity[maxEntities];

		for (int i = 0;i<maxEntities; i++) {
			entityIDs[i] = i;
		}
	}

	~EntityManager() {
		if (pointer != 0) {
			LOGGER->warn("%d entities have not been destroyed.",pointer);
		}

		delete[] entityIDs;
	}

	Entity createEntity() {
		if (pointer> m_maxEntities-1) {
			LOGGER->warn("Cannot create entity, no entity IDs left.");
			return -1;
		}

		Entity entity = entityIDs[pointer];
		pointer++;
		return entity;
	}

	void destroyEntity(Entity entity) {
		if (pointer < 1) {
			LOGGER->warn("Cannot destroy entity, no space left to return ID.");
			return;
		}

		pointer--;
		entityIDs[pointer] = entity;
	}

private:
	int m_maxEntities;

	Entity* entityIDs;
	int pointer=0;
};