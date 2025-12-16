#include "GameEngine.h"

#include "src/systems/System.h"

#include <iostream> 

namespace Fierce {
	GameEngine::GameEngine(){
		m_systemManager = new SystemManager();
		m_plattform = new Plattform();

		//Create plattform systems
		m_timeDateSystem = m_plattform->createTimeDateSystem();
		m_fileSystem = m_plattform->createFileSystem();
		m_loggingSystem = m_plattform->createLoggingSystem();
		m_inputSystem = m_plattform->createInputSystem();
		m_windowSystem = m_plattform->createWindowSystem();

		//Link systems
		((System*)m_timeDateSystem)->linkSystem((System*)m_loggingSystem);

		((System*)m_fileSystem)->linkSystem((System*)m_loggingSystem);

		((System*)m_loggingSystem)->linkSystem((System*)m_timeDateSystem);
		((System*)m_loggingSystem)->linkSystem((System*)m_fileSystem);

		((System*)m_inputSystem)->linkSystem((System*)m_loggingSystem);

		((System*)m_windowSystem)->linkSystem((System*)m_loggingSystem);
		((System*)m_windowSystem)->linkSystem((System*)m_inputSystem);

		//Add systems to manager
		m_systemManager->addSystem((System*)m_timeDateSystem);
		m_systemManager->addSystem((System*)m_fileSystem);
		m_systemManager->addSystem((System*)m_loggingSystem);
		m_systemManager->addSystem((System*)m_inputSystem);
		m_systemManager->addSystem((System*)m_windowSystem);

		//Add system rules
		m_systemManager->addRule((System*)m_loggingSystem,SYSTEM_RULE_TYPE::INIT_FIRST,nullptr);
		m_systemManager->addRule(m_loggingSystem, SYSTEM_RULE_TYPE::CLEANUP_LAST, nullptr);

		//Sort and intialize systems
		m_systemManager->sortAllSystems();
		m_systemManager->initAllSystems();
	}

	GameEngine::~GameEngine(){
		m_systemManager->cleanUpAllSystems();

		m_plattform->deleteTimeDateSystem(m_timeDateSystem);
		m_plattform->deleteFileSystem(m_fileSystem);
		m_plattform->deleteLoggingSystem(m_loggingSystem);
		m_plattform->deleteInputSystem(m_inputSystem);
		m_plattform->deleteWindowSystem(m_windowSystem);

		delete m_plattform;
		delete m_systemManager;
	}

	void GameEngine::run() {
		m_systemManager->updateAllSystems();
	}
}//end namespace