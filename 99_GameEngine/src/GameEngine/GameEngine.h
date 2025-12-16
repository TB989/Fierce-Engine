#pragma once

#include "src/GameEngine/SystemManager.h"
#include "src/PlatformLayer/include/Plattform.h"

namespace Fierce{
	class GameEngine{
	public:
		GameEngine();
		~GameEngine();

		void run();

	private:
		SystemManager* m_systemManager=nullptr;
		Plattform* m_plattform = nullptr;

		ITimeDateSystem* m_timeDateSystem=nullptr;
		IFileSystem* m_fileSystem = nullptr;
		ILoggingSystem* m_loggingSystem = nullptr;
		IInputSystem* m_inputSystem = nullptr;
		IWindowSystem* m_windowSystem = nullptr;
	};
}//end namespace