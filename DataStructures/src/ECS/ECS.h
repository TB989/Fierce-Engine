#pragma once

#include "Archetype.h"
#include "EntityManager.h"
#include "System.h"
#include "Types.h"
#include "src/Common/Hashmap.h"
#include "Logger.h"
#include <typeinfo>

class ECS {
public:
	ECS() {
		m_logger = new Logger("ECS");
		m_entityManager = new EntityManager(100);
		m_archetypeRegistry = new HashMap<ArchetypeId, Archetype*>(50);
		m_entityToArchetypeList = new HashMap<EntityId, ArchetypeId>(100);
		m_systemRegistry = new HashMap<const char*,System*>(50);
	}

	~ECS() {
		if (m_componentRegistry->getSize() != 0) {
			m_logger->warn("%d component types have not been unregistered.", m_componentRegistry->getSize());
		}

		delete m_componentRegistry;
		delete m_archetypeRegistry;
		delete m_entityToArchetypeList;
		delete m_entityManager;
		delete m_logger;
	}

	//##### Entities #####
	EntityId createEntity(ArchetypeId archetype) {
		EntityId entity = m_entityManager->createEntity();
		m_entityToArchetypeList->put(entity, archetype);
		return entity;
	}

	void destroyEntity(EntityId entity) {
		ArchetypeId id = m_entityToArchetypeList->get(entity)->getValue();
		Archetype* archetype = m_archetypeRegistry->get(id)->getValue();
		archetype->onEntityDestroyed(entity);
		m_entityToArchetypeList->remove(entity);
		if (archetype->isEmpty()) {
			m_archetypeRegistry->remove(id);
			delete archetype;
		}
		m_entityManager->destroyEntity(entity);
	}
	//####################

	//##### Components #####
	template <class C>
	bool registerComponent(ComponentId id) {
		const char* componentName = typeid(C).name();
		if (m_componentRegistry->has(componentName)) {
			m_logger->warn("Component type %s has already been registered.",componentName);
			return false;
		}
		else {
			m_componentRegistry->put(componentName,id);
			return true;
		}
	}

	template <class C>
	bool unregisterComponent() {
		const char* componentName = typeid(C).name();
		if (!m_componentRegistry->has(componentName)) {
			m_logger->warn("Component type %s has never been registered.", componentName);
			return false;
		}
		else {
			m_componentRegistry->remove(componentName);
			return true;
		}
	}

	template <class T>
	bool addComponent(EntityId entity, T& component) {
		ArchetypeId oldArchetypeId;
		ArchetypeId newArchetypeId;
		Archetype* oldArchetype;
		Archetype* newArchetype;

		//Find old archetype
		auto nodeOld = m_entityToArchetypeList->get(entity);
		if (nodeOld == nullptr) {
			oldArchetypeId = 0;
			oldArchetype = nullptr;
		}
		else {
			oldArchetypeId = nodeOld->getValue();
			oldArchetype = m_archetypeRegistry->get(oldArchetypeId)->getValue();
		}

		//Find new archetype
		newArchetypeId= ECS::IdGenerator<T>::getArchetypeId(oldArchetypeId);
		auto nodeNew = m_archetypeRegistry->get(newArchetypeId);
		if (nodeNew == nullptr) {
			newArchetype = new Archetype(newArchetypeId);
			checkAddedArchetypeWithSystems(newArchetype);
			m_archetypeRegistry->put(newArchetypeId, newArchetype);
		}
		else {
			newArchetype = nodeNew->getValue();
		}

		//Update entity to archetype list
		m_entityToArchetypeList->remove(entity);
		m_entityToArchetypeList->put(entity,newArchetypeId);

		//Transfer components
		if (oldArchetype != nullptr) {
			oldArchetype->transferComponentsTo(entity,newArchetype);
		}

		//Add Component
		newArchetype->addComponent(entity,component);

		//Check if old archetype is empty
		if (oldArchetype->isEmpty()) {
			m_archetypeRegistry->remove(oldArchetypeId);
			checkRemovedArchetypeWithSystems(oldArchetype);
			delete oldArchetype;
		}

		return true;
	}

	template <class T>
	bool removeComponent(EntityId entity) {
		ArchetypeId oldArchetypeId;
		ArchetypeId newArchetypeId;
		Archetype* oldArchetype;
		Archetype* newArchetype;

		//Find old archetype
		auto nodeOld = m_entityToArchetypeList->get(entity);
		if (nodeOld == nullptr) {
			oldArchetypeId = 0;
			oldArchetype = nullptr;
		}
		else {
			oldArchetypeId = nodeOld->getValue();
			oldArchetype = m_archetypeRegistry->get(oldArchetypeId)->getValue();
		}

		//Find new archetype
		newArchetypeId = ECS::IdGenerator<T>::getArchetypeId(oldArchetypeId,true);
		auto nodeNew = m_archetypeRegistry->get(newArchetypeId);
		if (nodeNew == nullptr) {
			newArchetype = new Archetype(newArchetypeId);
			checkAddedArchetypeWithSystems(newArchetype);
			m_archetypeRegistry->put(newArchetypeId, newArchetype);
		}
		else {
			newArchetype = nodeNew->getValue();
		}

		//Update entity to archetype list
		m_entityToArchetypeList->remove(entity);
		m_entityToArchetypeList->put(entity, newArchetypeId);

		//Transfer components
		if (oldArchetype != nullptr) {
			oldArchetype->transferComponentsTo(entity, newArchetype);
		}

		newArchetype->removeComponentVector<T>();

		//Check if old archetype is empty
		if (oldArchetype->isEmpty()) {
			m_archetypeRegistry->remove(oldArchetypeId);
			checkRemovedArchetypeWithSystems(oldArchetype);
			delete oldArchetype;
		}

		return true;
	}

	template <class T>
	T* getComponent(EntityId entity) {
		auto node = m_entityToArchetypeList->get(entity);
		if (node == nullptr) {
			return nullptr;
		}
		ArchetypeId archetypeId = node->getValue();
		Archetype* archetype = m_archetypeRegistry->get(archetypeId)->getValue();
		return archetype->getComponent<T>(entity);
	}

	//#####################

	//##### House keeping #####
	int getNumEntities() {
		return m_entityToArchetypeList->getSize();
	}

	int getNumArchetypes() {
		return m_archetypeRegistry->getSize();
	}

	int getNumComponents() {
		return m_componentRegistry->getSize();
	}

	void printComponentRegistry() {
		m_logger->info("Component registry:");
		auto iterator = m_componentRegistry->getIterator();
		iterator->reset();
		while (iterator->advance()!=nullptr) {
			m_logger->info("\t%-40.40s%-40.0d",iterator->get()->getKey(), iterator->get()->getValue());
		}
	}

	void printEntityToArchetypeList() {
		m_logger->info("Entities:");
		auto iterator = m_entityToArchetypeList->getIterator();
		iterator->reset();
		while (iterator->advance() != nullptr) {
			m_logger->info("\t%-40.0d%-40.0d", iterator->get()->getKey(), iterator->get()->getValue());
		}
	}

	void uint32_to_binary(uint32_t n, char* binary) {
		int i = 0;
		for (int j = 31; j >= 0; j--) {
			binary[i++] = ((n >> j) & 1) + '0';
		}
		binary[32] = '\0';
	}

	void printArchetypeRegistry() {
		m_logger->info("Archetype registry:");
		auto iterator = m_archetypeRegistry->getIterator();
		iterator->reset();
		while (iterator->advance() != nullptr) {
			char binary[33];
			uint32_to_binary(iterator->get()->getKey(), binary);
			m_logger->info("\t%-40.0d%-40.40s", iterator->get()->getKey(),binary);
		}
	}

	void printArchetypes() {
		m_logger->info("Archetypes:");
		auto iterator = m_archetypeRegistry->getIterator();
		iterator->reset();
		while (iterator->advance() != nullptr) {
			ArchetypeId id = iterator->get()->getKey();
			Archetype* archetype= iterator->get()->getValue();
			m_logger->info("\tArchetype #%d:", id);
			archetype->print();
		}
	}

	void print() {
		m_logger->info("##################################################################################");
		m_logger->info("################################ ECS #############################################");
		m_logger->info("##################################################################################");
		printComponentRegistry();
		printArchetypeRegistry();
		printEntityToArchetypeList();
		printArchetypes();
		m_logger->info("##################################################################################");
		m_logger->info("##################################################################################");
		m_logger->info("##################################################################################");
	}
	//#####################

	//##### Archetypes #####
	template<typename... Types>
	struct IdGenerator{
		static ArchetypeId getArchetypeId(ArchetypeId id=0,bool reset=false) {
			return id;
		}
	};

	template<typename T, typename... Rest>
	struct IdGenerator<T, Rest...> {
		static ArchetypeId getArchetypeId(ArchetypeId id=0, bool reset = false) {
			ArchetypeId id_intern = id;
			auto node = m_componentRegistry->get(typeid(T).name());
			if (node != nullptr) {
				ComponentId mask = node->getValue();
				if (reset) {
					id_intern &= ~(1 << mask);
				}
				else {
					id_intern |= (1 << mask);
				}
			}
			return IdGenerator<Rest...>::getArchetypeId(id_intern);
		}
	};

	Archetype* getOrCreateArchetype(EntityId entityId,ArchetypeId id) {
		auto node = m_archetypeRegistry->get(id);
		if (node == nullptr) {
			Archetype* archetype = new Archetype(id);
			checkAddedArchetypeWithSystems(archetype);
			m_archetypeRegistry->put(id,archetype);
			m_entityToArchetypeList->put(entityId,id);
			return archetype;
		}
		else {
			m_entityToArchetypeList->put(entityId, id);
			return node->getValue();
		}
	}
	//######################

	//##### Systems #####
	template <class S>
	bool registerSystem(System* system){
		if (m_systemRegistry->has(typeid(S).name())) {
			return false;
		}
		m_systemRegistry->put(typeid(S).name(),system);

		return true;
	}

	template <class S>
	bool unregisterSystem() {
		if (m_systemRegistry->has(typeid(S).name())) {
			auto node=m_systemRegistry->get(typeid(S).name());
			delete node->getValue();
			m_systemRegistry->remove(typeid(S).name());
			return true;
		}

		return false;
	}

	bool areBitsSet(ArchetypeId ArchetypeIdSystem,ArchetypeId archetypeId) {
		ArchetypeId result = ArchetypeIdSystem & archetypeId;
		return result == ArchetypeIdSystem;
	}

	void updateSystemArchetypes(System* system) {
		system->clearArchetypes();
		auto iterator = m_archetypeRegistry->getIterator();
		iterator->reset();
		while (iterator->advance()!=nullptr) {
			if (areBitsSet(system->getArchetypeSystemId(),iterator->get()->getKey())) {
				system->addArchetype(iterator->get()->getValue());
			}
		}
	}

	void checkAddedArchetypeWithSystems(Archetype* archetype) {
		System* system = nullptr;
		auto iterator = m_systemRegistry->getIterator();
		iterator->reset();
		while (iterator->advance() != nullptr) {
			system = iterator->get()->getValue();
			if (areBitsSet(system->getArchetypeSystemId(),archetype->getId())) {
				system->addArchetype(archetype);
			}
		}
	}

	void checkRemovedArchetypeWithSystems(Archetype* archetype) {
		System* system = nullptr;
		auto iterator = m_systemRegistry->getIterator();
		iterator->reset();
		while (iterator->advance() != nullptr) {
			system = iterator->get()->getValue();
			system->removeArchetype(archetype);
		}
	}

	template<class S, class C>
	bool systemAddComponent() {
		//Find system
		auto nodeSystem = m_systemRegistry->get(typeid(S).name());
		if (nodeSystem == nullptr) {
			return false;
		}
		System* system = nodeSystem->getValue();

		//Find component
		auto nodeComponent = m_componentRegistry->get(typeid(C).name());
		if (nodeComponent == nullptr) {
			return false;
		}
		ComponentId id = nodeComponent->getValue();

		//Set component flag
		system->setComponentFlag(id);

		//Update system archetypes
		updateSystemArchetypes(system);

		return true;
	}
	//###################

private:
	Logger* m_logger;
	EntityManager* m_entityManager;
	static HashMap<const char*, ComponentId>* m_componentRegistry;
	HashMap<ArchetypeId, Archetype*>* m_archetypeRegistry;
	HashMap<EntityId, ArchetypeId>* m_entityToArchetypeList;
	HashMap<const char*, System*>* m_systemRegistry;
};