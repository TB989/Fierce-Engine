#include "GameEngine.h"

#include "src/systems/System.h"

namespace Fierce {
	GameEngine::GameEngine(){
		m_systemManager = new SystemManager();
		m_plattform = new Plattform();
		m_layerStack = new LayerStack(m_systemManager);

		//Create plattform systems
		createSystems();
		linkSystems();
		addSystemsToManager();
		addSystemRules();

		//Sort and intialize systems
		m_systemManager->sortAllSystems();
		m_systemManager->initAllSystems();//TODO: Rendering System needs Window handle before init

		//Create core logger and timer
		m_logger = m_loggingSystem->createLogger("CORE", true, "ALL_LOGS");
		m_timer = m_timeDateSystem->createTimer();

		//Read settings
		IParser_Ini* parser = m_parsingSystem->createParser_Ini("");
		parser->parseFile("Engine.ini", m_settings);
		m_parsingSystem->deleteParser(parser);

		//Create window
		m_window = m_windowSystem->createWindow("Fierce Engine", m_settings.windowMode, m_settings.width, m_settings.height);

		//Loading App
		loadApp();
	}

	GameEngine::~GameEngine(){
		FreeLibrary(appDLL);

		m_loggingSystem->deleteLogger(m_logger);
		m_timeDateSystem->deleteTimer(m_timer);
		m_windowSystem->deleteWindow(m_window);

		m_systemManager->cleanUpAllSystems();

		deleteSystems();

		delete m_layerStack;
		delete m_plattform;
		delete m_systemManager;
	}

	void GameEngine::run() {
		m_running = true;
		m_window->show();
		m_timer->start();
		while (m_running) {
			m_systemManager->updateAllSystems();
			if (m_window->isClosing()) {
				m_running = false;
			}
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
		m_geometrySystem = new GeometrySystem();
		m_mathSystem = new MathSystem();
		m_renderSystem = new RenderSystem();
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

		m_renderSystem->linkSystem(m_loggingSystem);
		m_renderSystem->linkSystem(m_fileSystem);
		m_renderSystem->linkSystem(m_parsingSystem);
	}

	void GameEngine::addSystemsToManager(){
		m_systemManager->addSystem(m_timeDateSystem);
		m_systemManager->addSystem(m_fileSystem);
		m_systemManager->addSystem(m_loggingSystem);
		m_systemManager->addSystem(m_inputSystem);
		m_systemManager->addSystem(m_windowSystem);
		m_systemManager->addSystem(m_parsingSystem);
		m_systemManager->addSystem(m_geometrySystem);
		m_systemManager->addSystem(m_mathSystem);
		m_systemManager->addSystem(m_renderSystem);
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
		delete m_geometrySystem;
		delete m_mathSystem;
		delete m_renderSystem;
	}

	void GameEngine::loadApp(){
		appDLL = LoadLibraryA(m_settings.app.c_str());
		if (!appDLL) {
			m_logger->error("Failed to load App: %s", m_settings.app.c_str());
			return;
		}
		else {
			m_logger->info("Loading App: %s", m_settings.app.c_str());
		}

		auto createFunc = (initAppFunc)GetProcAddress(appDLL, "initApp");
		if (!createFunc) {
			m_logger->error("Failed to load function %s from App %s.", "initApp",m_settings.app.c_str());
			FreeLibrary(appDLL);
			return;
		}
		else {
			createFunc(m_layerStack);
		}
	}
}//end namespace