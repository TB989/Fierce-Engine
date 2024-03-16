#pragma once

#include <typeinfo>
#include "Types.h"
#include "src/Common/Hashmap.h"
#include "Logger.h"

class IComponentVector {
public:
	virtual bool removeComponent(EntityId entity) = 0;
	virtual bool onEntityDestroyed(EntityId entity) = 0;
	virtual bool transferComponentsTo(EntityId entity, IComponentVector* target) = 0;
	virtual bool isEmpty()=0;
	virtual IComponentVector* createEmptyClone()=0;
	virtual int getSize() = 0; 
	virtual void print() = 0;
};

template <typename T>
class ComponentVector : public IComponentVector {
public:
	ComponentVector() = delete;

	ComponentVector(int capacity) {
		m_logger = new Logger("COM_VEC");

		m_capacity = capacity;
		m_size = 0;
		m_components = new T[m_capacity];

		m_entity_to_index_map = new HashMap<EntityId, size_t>(m_capacity);
		m_index_to_entity_map = new HashMap<size_t, EntityId>(m_capacity);
	}

	~ComponentVector() {
		if (m_size != 0) {
			m_logger->warn("%d components have not been removed for component vector of type %s.",m_size, typeid(T).name());
		}

		delete m_index_to_entity_map;
		delete m_entity_to_index_map;
		delete[] m_components;
		delete m_logger;
	}

	bool isEmpty() {
		return m_size == 0;
	}

	IComponentVector* createEmptyClone() {
		//TODO: Where to get capacity?
		return new ComponentVector<T>(m_capacity);
	}

	bool addComponent(EntityId entity, T& component) {
		if (m_size>=m_capacity) {
			return false;
		}

		if (m_entity_to_index_map->get(entity)!=nullptr) {
			return false;
		}

		int index = m_size;

		m_components[index] = component;

		m_entity_to_index_map->put(entity,index);
		m_index_to_entity_map->put(index,entity);

		m_size++;

		return true;
	}

	bool removeComponent(EntityId entity) {
		auto node_index = m_entity_to_index_map->get(entity);

		if (node_index==nullptr) {
			return false;
		}

		int indexRemoved = node_index->getValue();
		int indexLast = m_size - 1;
		EntityId lastEntity = m_index_to_entity_map->get(indexLast)->getValue();

		//Move entity
		m_components[indexRemoved] = m_components[indexLast];
		m_entity_to_index_map->put(lastEntity,indexRemoved);
		m_index_to_entity_map->put(indexRemoved,lastEntity);

		//Remove entity
		m_components[indexLast] = T();
		m_entity_to_index_map->remove(entity);
		m_index_to_entity_map->remove(indexLast);

		m_size--;

		return true;
	}

	T* getComponent(EntityId entity) {
		auto node = m_entity_to_index_map->get(entity);
		if (node == nullptr) {
			return nullptr;
		}
		size_t index = node->getValue();

		return &m_components[index];
	}

	T* getComponentAtIndex(int index) {
		return &m_components[index];
	}

	bool hasComponent(EntityId entity) {
		auto node=m_entity_to_index_map->get(entity);
		if (node == nullptr) {
			return false;
		}
		return true;
	}

	bool onEntityDestroyed(EntityId entity) {
		auto node=m_entity_to_index_map->get(entity);
		if (node==nullptr) {
			return false;
		}
		removeComponent(entity);
		return true;
	}

	bool transferComponentsTo(EntityId entity,IComponentVector* target) {
		ComponentVector<T>* newVector = (ComponentVector<T>*)target;
		T* component = this->getComponent(entity);
		if(component==nullptr){
			return false;
		}
		newVector->addComponent(entity,*component);
		this->removeComponent(entity);
		return true;
	}

	void print() {
		m_logger->info("\t\t\tCapacity: %d",m_capacity);
		m_logger->info("\t\t\tSize: %d", m_size);
		for (int i = 0;i<m_size;i++) {
			EntityId entity = m_index_to_entity_map->get(i)->getValue();
			m_logger->info("\t\t\t%-20.0d%-20.0p", entity,m_components[i]);
		}
	}

	int getSize() {
		return m_size;
	}

private:
	int m_capacity;
	int m_size;
	T* m_components;

	HashMap<EntityId, size_t>* m_entity_to_index_map;
	HashMap<size_t, EntityId>* m_index_to_entity_map;

	Logger* m_logger;
};