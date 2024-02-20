#pragma once

#include "utils/Logging.h"

#include "ComponentArray.h"

#include <unordered_map>
#include <typeinfo>

using Entity = int;

class ComponentManager{
public:
	~ComponentManager() {
		if (!m_componentArrays.empty()) {
			LOGGER123->warn("The following components have not been unregistered:");
			for (auto& it : m_componentArrays) {
				LOGGER123->warn("%s",it.first);
			}
		}
	}

	template<typename T>
	void registerComponent(int maxComponents) {
		const char* typeName = typeid(T).name();

		if (m_componentArrays.find(typeName)!= m_componentArrays.end()) {
			LOGGER123->warn("Trying to register component %s more than once.", typeName);
			return;
		}

		m_componentArrays.insert({ typeName, new ComponentArray<T>(maxComponents) });
	}

	template<typename T>
	void unregisterComponent() {
		const char* typeName = typeid(T).name();

		if (m_componentArrays.find(typeName) == m_componentArrays.end()) {
			LOGGER123->warn("Trying to unregister component %s, which has never been registered, or already has been unregistered.", typeName);
			return;
		}

		ComponentArray<T>* arr = GetComponentArray<T>();
		delete arr;
		m_componentArrays.erase(typeName);
	}

	template<typename T>
	void addComponent(Entity entity, T& component){
		LOGGER123->warn("Start of add comp");
		const char* typeName = typeid(T).name();
		if (m_componentArrays.find(typeName) == m_componentArrays.end()) {
			LOGGER123->warn("Cannot add component %s, as component has never been registered.", typeName);
			return;
		}
		GetComponentArray<T>()->insertComponent(entity,component);
		LOGGER123->warn("End of add comp");
	}

	template<typename T>
	void removeComponent(Entity entity){
		const char* typeName = typeid(T).name();

		if (m_componentArrays.find(typeName) == m_componentArrays.end()) {
			LOGGER123->warn("Cannot remove component %s, as component has never been registered.", typeName);
			return;
		}

		GetComponentArray<T>()->removeComponent(entity);
	}

	template<typename T>
	T* getComponent(Entity entity){
		const char* typeName = typeid(T).name();

		if (m_componentArrays.find(typeName) == m_componentArrays.end()) {
			LOGGER123->warn("Cannot get component %s, as component has never been registered.", typeName);
			return T();
		}

		return GetComponentArray<T>()->getComponent(entity);
	}

private:
	std::unordered_map<const char*, IComponentArray*> m_componentArrays{};

	template<typename T>
	ComponentArray<T>* GetComponentArray(){
		const char* typeName = typeid(T).name();

		return (ComponentArray<T>*)(m_componentArrays[typeName]);
	}
};