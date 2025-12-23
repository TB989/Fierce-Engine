#pragma once

#include "src/GameEngine/SystemManager.h"
#include "src/PlatformLayer/include/Plattform.h"
#include "src/Parsers/ParsingSystem.h"

namespace Fierce{
	class GameEngine{
	public:
		GameEngine();
		~GameEngine();

		void run();

	private:
		void createSystems();
		void linkSystems();
		void addSystemsToManager();
		void addSystemRules();
		void deleteSystems();

	private:
		SystemManager* m_systemManager=nullptr;
		Plattform* m_plattform = nullptr;

		bool m_running = false;
		ILogger* m_logger = nullptr;
		ITimer* m_timer = nullptr;
		EngineSettings m_settings = {};
		IWindow* m_window = nullptr;

		ITimeDateSystem* m_timeDateSystem=nullptr;
		IFileSystem* m_fileSystem = nullptr;
		ILoggingSystem* m_loggingSystem = nullptr;
		IInputSystem* m_inputSystem = nullptr;
		IWindowSystem* m_windowSystem = nullptr;
		IParsingSystem* m_parsingSystem = nullptr;
	};
}//end namespace