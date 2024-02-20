#pragma once

#include "Archetype.h"
#include "EntityManager.h"
#include  "Hashmap.h"
#include "Logger.h"

#include <typeinfo>
#include <cstdarg>

class ECS {
public:
	ECS();
	~ECS();

	//##### Entities #####
	EntityId createEntity();
	void destroyEntity(EntityId entity);
	//####################

	//##### Components #####
	template <class C>
	bool registerComponent(ComponentId id) {
		const char* componentName = typeid(C).name();
		if (componentRegistry->has(componentName)) {
			logger->warn("Component type %s has already been registered.",componentName);
			return false;
		}
		else {
			componentRegistry->put(componentName,id);
			logger->info("Component type %s has successfully been registered with id %d.", componentName,id);
			return true;
		}
	}

	template <class C>
	bool unregisterComponent() {
		const char* componentName = typeid(C).name();
		if (!componentRegistry->has(componentName)) {
			logger->warn("Component type %s has never been registered.", componentName);
			return false;
		}
		else {
			componentRegistry->remove(componentName);
			logger->info("Component type %s has successfully been unregistered.", componentName);
			return true;
		}
	}

	template <class T>
	bool addComponent(EntityId entity, T& component) {
		return true;
	}

	template <class T>
	bool removeComponent(EntityId entity) {
		return true;
	}
	//#####################

	//##### Archetypes #####
	template<typename... Types>
	struct IdGenerator{
		static ArchetypeId getArchetypeId(ArchetypeId id=0) {
			return id;
		}
	};

	template<typename T, typename... Rest>
	struct IdGenerator<T, Rest...> {
		static ArchetypeId getArchetypeId(ArchetypeId id=0) {
			ArchetypeId id_intern = id;
			auto node = componentRegistry->get(typeid(T).name());
			if (node != nullptr) {
				ComponentId mask = node->getValue();
				id_intern |= (1 << mask);
			}
			return IdGenerator<Rest...>::getArchetypeId(id_intern);
		}
	};

	Archetype* getOrCreateArchetype(ArchetypeId id) {
		auto node = archetypeRegistry->get(id);
		if (node == nullptr) {
			Archetype* archetype = new Archetype(id);
			archetypeRegistry->put(id,archetype);
			return archetype;
		}
		else {
			return node->getValue();
		}
	}
	//######################

	//##### Systems #####
	template <class S>
	S* registerSystem(S& system){
		return nullptr;
	}

	template<class S, class... C>
	bool systemAddComponents() {
		return true;
	}
	//###################

private:
	Logger* logger;
	EntityManager* entityManager;
	static HashMap<const char*, ComponentId>* componentRegistry;
	HashMap<ArchetypeId, Archetype*>* archetypeRegistry;
};