#pragma once

#include "src/FierceStrings.h"
#include <unordered_map>

namespace Fierce {
	
	template<class T>
	class VK_Manager{
	public:
		VK_Manager() {}
		inline ~VK_Manager() {
			for (auto& it : m_objects) {
				delete it.second;
			}
		}

		inline void add(std::string name, T object) {
			m_objects[name] = object;
		}

		inline T get(std::string name) {
			return m_objects[name];
		}

	private:
		std::unordered_map<std::string, T> m_objects;
	};
}//end namespace