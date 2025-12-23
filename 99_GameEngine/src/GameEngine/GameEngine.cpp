#include "GameEngine.h"

#include "src/systems/System.h"

namespace Fierce {
	GameEngine::GameEngine(){
		m_systemManager = new SystemManager();
		m_plattform = new Plattform();

		//Create plattform systems
		createSystems();
		linkSystems();
		addSystemsToManager();
		addSystemRules();

		//Sort and intialize systems
		m_systemManager->sortAllSystems();
		m_systemManager->initAllSystems();

		//Create core logger and timer
		m_logger = m_loggingSystem->createLogger("CORE", true, "ALL_LOGS");
		m_timer = m_timeDateSystem->createTimer();

		//Read settings
		IParser_Ini* parser = m_parsingSystem->createParser_Ini("");
		parser->parseFile("Engine.ini", m_settings);
		m_parsingSystem->deleteParser(parser);

		//Create window
		m_window = m_windowSystem->createWindow("Fierce Engine", m_settings.windowMode, m_settings.width, m_settings.height);
	}

	GameEngine::~GameEngine(){
		m_loggingSystem->deleteLogger(m_logger);
		m_timeDateSystem->deleteTimer(m_timer);
		m_windowSystem->deleteWindow(m_window);

		m_systemManager->cleanUpAllSystems();

		deleteSystems();

		delete m_plattform;
		delete m_systemManager;
	}

	void GameEngine::run() {
		m_running = true;
		m_window->show();
		m_timer->start();
		while (m_running) {
			m_systemManager->updateAllSystems();
		}
		m_timer->stop();
	}

	void GameEngine::createSystems(){
		m_timeDateSystem = m_plattform->createTimeDateSystem();
		m_fileSystem = m_plattform->createFileSystem();
		m_loggingSystem = m_plattform->createLoggingSystem();
		m_inputSystem = m_plattform->createInputSystem();
		m_windowSystem = m_plattform->createWindowSystem();
		m_parsingSystem = new ParsingSystem();
	}

	void GameEngine::linkSystems(){
		m_timeDateSystem->linkSystem(m_loggingSystem);

		m_fileSystem->linkSystem(m_loggingSystem);

		m_loggingSystem->linkSystem(m_timeDateSystem);
		m_loggingSystem->linkSystem(m_fileSystem);

		m_inputSystem->linkSystem(m_loggingSystem);

		m_windowSystem->linkSystem(m_loggingSystem);
		m_windowSystem->linkSystem(m_inputSystem);

		m_parsingSystem->linkSystem(m_fileSystem);
		m_parsingSystem->linkSystem(m_loggingSystem);
	}

	void GameEngine::addSystemsToManager(){
		m_systemManager->addSystem(m_timeDateSystem);
		m_systemManager->addSystem(m_fileSystem);
		m_systemManager->addSystem(m_loggingSystem);
		m_systemManager->addSystem(m_inputSystem);
		m_systemManager->addSystem(m_windowSystem);
		m_systemManager->addSystem(m_parsingSystem);
	}

	void GameEngine::addSystemRules(){
		m_systemManager->addRule(m_loggingSystem, SYSTEM_RULE_TYPE::INIT_FIRST, nullptr);
		m_systemManager->addRule(m_loggingSystem, SYSTEM_RULE_TYPE::CLEANUP_LAST, nullptr);
	}

	void GameEngine::deleteSystems(){
		m_plattform->deleteTimeDateSystem(m_timeDateSystem);
		m_plattform->deleteFileSystem(m_fileSystem);
		m_plattform->deleteLoggingSystem(m_loggingSystem);
		m_plattform->deleteInputSystem(m_inputSystem);
		m_plattform->deleteWindowSystem(m_windowSystem);
		delete m_parsingSystem;
	}
}//end namespace