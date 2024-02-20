#pragma once

#include "ComponentVector.h"
#include "Hashmap.h"
#include "Types.h"
#include <typeinfo>

class Archetype {
public:
	Archetype(ArchetypeId id);
	~Archetype();

	template <typename T>
	void addComponent(EntityId entity,T& component) {
		const char* componentName = typeid(T).name();

		auto node= componentVectors->get(componentName);
		if (node==nullptr) {
			ComponentVector<T>* componentVector = new ComponentVector<T>(50);
			componentVector->addComponent(entity, component);
			componentVectors->put(componentName,componentVector);
		}
		else {
			ComponentVector<T>* componentVector=(ComponentVector<T>*)node->getValue();
			componentVector->addComponent(entity, component);
		}
	}

	template <typename T>
	void removeComponent(EntityId entity) {
		const char* componentName = typeid(T).name();
		auto node = componentVectors->get(componentName);
		ComponentVector<T>* componentVector = (ComponentVector<T>*)node->getValue();
		componentVector->removeComponent(entity);
	}

	void onEntityDestroyed(EntityId entity) {
		auto iterator = componentVectors->getIterator();
		iterator->reset();
		while (iterator->advance() != nullptr) {
			auto node = iterator->get();
			IComponentVector* componentVector = node->getValue();
			componentVector->onEntityDestroyed(entity);
		}
		numEntities--;
	}

	ArchetypeId getId();

private:
	ArchetypeId archetypeId;
	int numEntities;
	HashMap<const char*, IComponentVector*>* componentVectors;
};