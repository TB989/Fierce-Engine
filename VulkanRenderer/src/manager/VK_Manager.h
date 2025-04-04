#pragma once

#include "src/utils/FierceStrings.h"
#include <unordered_map>
#include <vector>

namespace Fierce {
	
	template<class T>
	class VK_Manager{
	public:
		VK_Manager() {}
		inline ~VK_Manager() {
			for (auto& object : m_objects) {
				delete object;
			}
		}

		inline void add(std::string name, T object) {
			int index = m_objects.size();
			m_objects.push_back(object);
			m_indexMap[name] = index;
		}

		inline T get(std::string name) {
			int index = m_indexMap[name];
			return m_objects[index];
		}

		inline T get(int index) {
			return m_objects[index];
		}

	private:
		std::unordered_map<std::string, int> m_indexMap;
		std::vector<T> m_objects;
	};
}//end namespace