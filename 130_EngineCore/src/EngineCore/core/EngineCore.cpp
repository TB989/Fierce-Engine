#include "EngineCore.h"

#include "src/PlatformLayer/include/Plattform.h"

#include "src/PlatformLayer/Win32/Win32_Window.h"

namespace Fierce {

	bool EngineCore::m_running = false;

	EngineCore::EngineCore(){
		corePreInit();
	}

	EngineCore::~EngineCore(){
		
	}

	void EngineCore::run(){
		coreInit();
		init();
		m_renderSystem->postInit();

		m_running = true;
		m_window->show();
		m_timer->start();
		while (m_running) {
			coreUpdate();
			update(m_timer->getElapsedTime());
			m_renderSystem->startFrame();
			coreRender();
			render();
			renderGUI(m_guiSystem->getGraphicsContext());
			m_renderSystem->endFrame();
		}
		m_timer->stop();

		cleanUp();
		coreCleanUp();
	}

	void EngineCore::stop(){
		m_running = false;
	}

	void EngineCore::corePreInit(){
		m_plattform = new Plattform();

		//Create systems
		m_timeDateSystem = m_plattform->createTimeDateSystem();
		m_fileSystem = m_plattform->createFileSystem();
		m_loggingSystem = m_plattform->createLoggingSystem();
		m_parsingSystem = new ParsingSystem();
		m_geometrySystem = new GeometrySystem();

		//Link systems
		m_loggingSystem->linkSystem(m_timeDateSystem);
		m_loggingSystem->linkSystem(m_fileSystem);

		m_parsingSystem->linkSystem(m_fileSystem);
		m_parsingSystem->linkSystem(m_loggingSystem);

		m_fileSystem->linkSystem(m_loggingSystem);
		m_timeDateSystem->linkSystem(m_loggingSystem);
		m_geometrySystem->linkSystem(m_loggingSystem);

		//Init systems
		m_loggingSystem->initSystem("C:/Users/tmbal/Desktop/Fierce-Engine/002_Assets/");//Must be initialised first
		m_timeDateSystem->initSystem("");
		m_fileSystem->initSystem("");
		m_parsingSystem->initSystem("");
		m_geometrySystem->initSystem("");

		//Create core logger and timer
		m_logger = m_loggingSystem->createLogger("CORE", true, "ALL_LOGS");
		m_timer = m_timeDateSystem->createTimer();

		//Read settings
		Parser_Ini* parser = m_parsingSystem->createParser_Ini("");
		parser->parseFile("Engine.ini", m_settings);
		m_parsingSystem->deleteParser(parser);

		//Create core logger and timer
		//m_logger = m_loggingSystem->createLogger("CORE", true, "ALL_LOGS");
		//m_timer = m_timeDateSystem->createTimer();
	}

	void EngineCore::coreInit(){
		//Create systems
		m_inputSystem = m_plattform->createInputSystem();
		m_windowSystem = m_plattform->createWindowSystem();
		m_renderSystem = new RenderSystem();
		m_guiSystem = new GUISystem();

		//Link systems
		m_inputSystem->linkSystem(m_loggingSystem);

		m_windowSystem->linkSystem(m_loggingSystem);
		m_windowSystem->linkSystem(m_inputSystem);

		m_renderSystem->linkSystem(m_loggingSystem);
		m_renderSystem->linkSystem(m_fileSystem);
		m_renderSystem->linkSystem(m_parsingSystem);

		m_guiSystem->linkSystem(m_loggingSystem);
		m_guiSystem->linkSystem(m_renderSystem);
		m_guiSystem->linkSystem(m_inputSystem);

		//Init systems
		m_inputSystem->initSystem(m_settings.assetPath);
		m_windowSystem->initSystem(m_settings.assetPath);

		//Create window
		m_window = m_windowSystem->createWindow("Fierce Engine", m_settings.windowMode, m_settings.width, m_settings.height);

		//Initialise render system after window creation, because it needs the window handle
		//Create graphics context
		m_renderSystem->setWindowHandle(((Win32_Window*)(m_window))->getHandle());
		m_renderSystem->initSystem(m_settings.assetPath);

		//Create Gui System after Render System, because it needs the graphics context from render system
		m_guiSystem->initSystem(m_settings.assetPath);
	}

	void EngineCore::coreUpdate(){
		m_timeDateSystem->updateSystem();
		m_fileSystem->updateSystem();
		m_loggingSystem->updateSystem();
		m_parsingSystem->updateSystem();
		m_geometrySystem->updateSystem();
		m_inputSystem->updateSystem();
		m_windowSystem->updateSystem();
		m_renderSystem->updateSystem();
	}

	void EngineCore::coreRender(){}

	void EngineCore::coreCleanUp(){
		//Delete window and timer and logger
		m_windowSystem->deleteWindow(m_window);
		m_timeDateSystem->deleteTimer(m_timer);
		m_loggingSystem->deleteLogger(m_logger);

		//Clean up systems
		m_guiSystem->cleanUpSystem();
		m_renderSystem->cleanUpSystem();
		m_windowSystem->cleanUpSystem();
		m_inputSystem->cleanUpSystem();
		m_geometrySystem->cleanUpSystem();
		m_parsingSystem->cleanUpSystem();
		m_timeDateSystem->cleanUpSystem();
		m_fileSystem->cleanUpSystem();
		m_loggingSystem->cleanUpSystem();//Must be destroyed last

		//Delete systems
		delete m_renderSystem;
		delete m_windowSystem;
		delete m_inputSystem;
		delete m_geometrySystem;
		delete m_parsingSystem;
		delete m_timeDateSystem;
		delete m_loggingSystem;
		delete m_fileSystem;
	}

}