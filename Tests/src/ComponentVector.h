#pragma once

#include "Types.h"
#include "Hashmap.h"

class IComponentVector {
public:
	virtual void onEntityDestroyed(EntityId entity) = 0;
};

template <typename T>
class ComponentVector : public IComponentVector {
public:
	ComponentVector() = delete;

	ComponentVector(int capacity) {
		m_capacity = capacity;
		size = 0;
		components = new T[capacity];

		entity_to_index_map = new HashMap<EntityId, size_t>(capacity);
		index_to_entity_map = new HashMap<size_t, EntityId>(capacity);
	}

	~ComponentVector() {
		delete[] components;
	}

	void addComponent(EntityId entity, T& component) {
		int index = size;

		components[index] = component;

		entity_to_index_map->put(entity,index);
		index_to_entity_map->put(index,entity);

		size++;
	}

	void removeComponent(EntityId entity) {
		int indexRemoved = entity_to_index_map->get(entity)->getValue();
		int indexLast = size - 1;
		EntityId lastEntity = index_to_entity_map->get(indexLast)->getValue();

		components[indexRemoved] = components[indexLast];

		entity_to_index_map->put(lastEntity,indexRemoved);
		index_to_entity_map->put(indexRemoved,lastEntity);

		size--;
	}

	void onEntityDestroyed(EntityId entity) {
		auto node=entity_to_index_map->get(entity);
		if (node!=nullptr) {
			removeComponent(entity);
		}
	}

private:
	int m_capacity;
	int size;
	T* components;

	HashMap<EntityId, size_t>* entity_to_index_map;
	HashMap<size_t, EntityId>* index_to_entity_map;
};