#pragma once

#include "ComponentVector.h"
#include "Types.h"
#include "src/Common/Hashmap.h"
#include "Logger.h"
#include <typeinfo>

class Archetype {
public:
	Archetype() {
		Archetype(50);
	}

	Archetype(ArchetypeId id) {
		m_logger = new Logger("ARCH");
		m_archetypeId = id;
		m_numComponentVectors = 0;
		m_componentVectors = new HashMap<const char*, IComponentVector*>(50);
	}

	~Archetype() {
		if (m_componentVectors->getSize()!=0) {
			m_logger->warn("%d components have not been removed for archetype %d.", m_componentVectors->getSize(), m_archetypeId);
		}
		delete m_componentVectors;
		m_logger;
	}

	template <typename T>
	void addComponent(EntityId entity,T& component) {
		const char* componentName = typeid(T).name();

		auto node= m_componentVectors->get(componentName);
		if (node==nullptr) {
			ComponentVector<T>* componentVector = new ComponentVector<T>(50);
			bool added=componentVector->addComponent(entity, component);
			m_componentVectors->put(componentName,componentVector);
			m_numComponentVectors++;
		}
		else {
			ComponentVector<T>* componentVector=(ComponentVector<T>*)node->getValue();
			componentVector->addComponent(entity, component);
		}
	}

	template <typename T>
	void addComponentVector(IComponentVector* componentVector) {
		m_componentVectors->put(typeid(T).name(), componentVector);
	}

	void addComponentVector(const char* name,IComponentVector* componentVector) {
		m_componentVectors->put(name,componentVector);
	}

	template <typename T>
	ComponentVector<T>* getComponentVector() {
		const char* componentName = typeid(T).name();
		auto node = m_componentVectors->get(componentName);
		if (node == nullptr) {
			return nullptr;
		}
		return (ComponentVector<T>*)node->getValue();
	}

	template <typename T>
	T* getComponent(EntityId entity) {
		ComponentVector<T>* vec = getComponentVector<T>();
		if (vec == nullptr) {
			return nullptr;
		}
		return vec->getComponent(entity);
	}

	IComponentVector* getComponentVector(const char* name) {
		auto node = m_componentVectors->get(name);
		if (node == nullptr) {
			return nullptr;
		}
		return node->getValue();
	}

	template <typename T>
	void removeComponent(EntityId entity) {
		const char* componentName = typeid(T).name();
		auto node = m_componentVectors->get(componentName);
		ComponentVector<T>* componentVector = (ComponentVector<T>*)node->getValue();
		componentVector->removeComponent(entity);
		if (componentVector->isEmpty()) {
			m_componentVectors->remove(componentName);
		}
	}

	void removeComponentVector(const char* name) {
		m_componentVectors->remove(name);
	}

	template <typename T>
	void removeComponentVector() {
		removeComponentVector(typeid(T).name());
	}

	void onEntityDestroyed(EntityId entity) {
		auto iterator = m_componentVectors->getIterator();
		iterator->reset();
		while (iterator->advance() != nullptr) {
			auto node = iterator->get();
			IComponentVector* componentVector = node->getValue();
			componentVector->onEntityDestroyed(entity);
		}
	}

	void transferComponentsTo(EntityId entity, Archetype* target) {
		auto iterator = m_componentVectors->getIterator();
		iterator->reset();
		while (iterator->advance() != nullptr) {
			auto node = iterator->get();
			const char* componentName = node->getKey();
			IComponentVector* componentVector = node->getValue();

			IComponentVector* targetVector = target->getComponentVector(componentName);
			if (targetVector == nullptr) {
				targetVector = componentVector->createEmptyClone();
				target->addComponentVector(componentName,targetVector);
			}
			
			componentVector->transferComponentsTo(entity,targetVector);
			componentVector->removeComponent(entity);
		}
	}

	ArchetypeId getId() {
		return m_archetypeId;
	}

	int getNumEntities() {
		if (m_componentVectors->getSize() == 0) {
			return 0;
		}

		auto iterator = m_componentVectors->getIterator();
		iterator->reset();
		iterator->advance();
		auto node=iterator->get();

		if (node == nullptr) {
			return 0;
		}

		IComponentVector* vec = node->getValue();
		return vec->getSize();
	}

	bool isEmpty() {
		return getNumEntities() == 0;
	}

	int getNumComponentVectors() {
		return m_numComponentVectors;
	}

	void print() {
		auto iterator = m_componentVectors->getIterator();
		iterator->reset();
		while (iterator->advance() != nullptr) {
			const char* name = iterator->get()->getKey();
			IComponentVector* vector= iterator->get()->getValue();
			m_logger->info("\t\tComponentVector %s:",name);
			vector->print();
		}
	}

private:
	Logger* m_logger;
	ArchetypeId m_archetypeId;
	int m_numComponentVectors;
	HashMap<const char*, IComponentVector*>* m_componentVectors;
};