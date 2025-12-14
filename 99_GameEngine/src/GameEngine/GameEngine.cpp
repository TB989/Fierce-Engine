#include "GameEngine.h"

#include "src/systems/System.h"

namespace Fierce {
	GameEngine::GameEngine(){
		m_systemManager = new SystemManager();
		m_plattform = new Plattform();

		m_timeDateSystem = m_plattform->createTimeDateSystem();

		m_systemManager->addSystem((System*)m_timeDateSystem);

		m_systemManager->sortAllSystems();
		m_systemManager->initAllSystems();
	}

	GameEngine::~GameEngine(){
		m_systemManager->cleanUpAllSystems();

		//TODO: Delete in Plattform
		delete m_timeDateSystem;
	}

	void GameEngine::run() {
		m_systemManager->updateAllSystems();
	}
}//end namespace