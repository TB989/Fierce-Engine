#pragma once

#include "src/systems/System.h"
#include "src/systems/ISystemManager.h"

#include <vector>

namespace Fierce {
	enum class SYSTEM_RULE_TYPE {
		INIT_FIRST,
		INIT_LAST,
		INIT_BEFORE,
		INIT_AFTER,

		UPDATE_FIRST,
		UPDATE_LAST,
		UPDATE_BEFORE,
		UPDATE_AFTER,

		CLEANUP_FIRST,
		CLEANUP_LAST,
		CLEANUP_BEFORE,
		CLEANUP_AFTER
	};

	class SystemManager:public ISystemManager{
	private:
		class SystemRule {
		public:
			SystemRule(System* system1, SYSTEM_RULE_TYPE ruleType, System* system2) {
				m_system1 = system1;
				m_ruleType = ruleType;
				m_system2 = system2;
			};

			System* m_system1;
			SYSTEM_RULE_TYPE m_ruleType;
			System* m_system2;
		};

	public:
		SystemManager();
		~SystemManager();

		System* getSystem(std::string name) override;

		void addSystem(System* system);
		void removeSystem(System* system);
		void addRule(System* system1,SYSTEM_RULE_TYPE ruleType,System* system2);

	public:
		void initAllSystems();
		void updateAllSystems();
		void cleanUpAllSystems();

		void sortAllSystems();

	private:
		std::vector<System*> sortSystems(std::vector<SystemRule*> rules);

	private:
		std::vector<System*> m_systems;
		std::vector<System*> m_systems_init;
		std::vector<System*> m_systems_update;
		std::vector<System*> m_systems_cleanUp;

		std::vector<SystemRule*> m_rules_init;
		std::vector<SystemRule*> m_rules_update;
		std::vector<SystemRule*> m_rules_cleanUp;
	};
}//end namespace