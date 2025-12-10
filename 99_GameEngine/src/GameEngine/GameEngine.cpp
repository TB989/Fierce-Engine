#include "GameEngine.h"

#include "src/GameEngine/TestSystems.h"

namespace Fierce {
	GameEngine::GameEngine(){
		m_systemManager = new SystemManager();

		system1 = new TestSystem1();
		system2 = new TestSystem2();
		system3 = new TestSystem3();

		m_systemManager->addSystem(system3);
		m_systemManager->addSystem(system1);
		m_systemManager->addSystem(system2);

		m_systemManager->addRule(system1,SYSTEM_RULE_TYPE::INIT_FIRST,nullptr);
		m_systemManager->addRule(system2, SYSTEM_RULE_TYPE::INIT_BEFORE, system3);

		m_systemManager->initAllSystems();
	}

	GameEngine::~GameEngine(){
		delete system1;
		delete system2;
		delete system3;
	}

	void GameEngine::run() {

	}
}//end namespace