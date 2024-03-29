#pragma once

#include "utils/Logging.h"

#include <unordered_map>

using Entity = int;
using Index = int;

class IComponentArray{};

template<typename T>
class ComponentArray : public IComponentArray {
public:
	ComponentArray(int maxComponents) {
		m_maxComponents = maxComponents;
		components = new T[maxComponents];
	}

	~ComponentArray() {
		if (pointer != 0) {
			LOGGER123->warn("%d components have not been removed.", pointer);
		}

		delete[] components;
	}

	void insertComponent(Entity entity, T& component){

		LOGGER123->error("Start of insert comp");

		if (entityToIndexMap.find(entity)!= entityToIndexMap.end()) {
			LOGGER123->warn("Trying to insert component more than once for entity %i.",entity);
			return;
		}

		if (pointer > m_maxComponents - 1) {
			LOGGER123->warn("Cannot add component, component array is full.");
			return;
		}

		Index newIndex = pointer;
		entityToIndexMap[entity] = newIndex;
		indexToEntityMap[newIndex] = entity;
		components[newIndex] = component;
		pointer++;

		LOGGER123->error("End of insert comp");
	}

	void removeComponent(Entity entity){
		if (entityToIndexMap.find(entity) == entityToIndexMap.end()) {
			LOGGER123->warn("Trying to remove nonexistent component for entity %i.", entity);
			return;
		}

		if (pointer < 1) {
			LOGGER123->warn("Cannot remove component for entity %i.",entity);
			return;
		}

		Index indexOfRemovedEntity = entityToIndexMap[entity];
		Index indexOfLastElement = pointer - 1;
		components[indexOfRemovedEntity] = components[indexOfLastElement];

		Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
		entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		entityToIndexMap.erase(entity);
		indexToEntityMap.erase(indexOfLastElement);

		pointer--;
	}

	T* getComponent(Entity entity){
		if (entityToIndexMap.find(entity) == entityToIndexMap.end()) {
			LOGGER123->warn("Component does not exist for entity %i.", entity);
			return T();
		}

		return components[entityToIndexMap[entity]];
	}
private:
	int m_maxComponents;

	T* components;
	int pointer = 0;
	std::unordered_map<Entity, Index> entityToIndexMap{};
	std::unordered_map<Index, Entity> indexToEntityMap{};
};