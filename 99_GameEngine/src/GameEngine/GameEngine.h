#pragma once

#include "src/systemManager/SystemManager.h"
#include "src/PlatformLayer/include/Plattform.h"
#include "src/Parsers/ParsingSystem.h"
#include "src/layerstack/LayerStack.h"
#include "src/GeometryLibrary/GeometrySystem.h"
#include "src/MathLibrary/MathSystem.h"
#include "src/VulkanRenderer/renderSystem/RenderSystem.h"

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

		void loadApp();

	private:
		SystemManager* m_systemManager=nullptr;
		Plattform* m_plattform = nullptr;
		LayerStack* m_layerStack = nullptr;

		//Misc
		bool m_running = false;
		ILogger* m_logger = nullptr;
		ITimer* m_timer = nullptr;
		EngineSettings m_settings = {};
		IWindow* m_window = nullptr;

		//Systems
		ITimeDateSystem* m_timeDateSystem=nullptr;
		IFileSystem* m_fileSystem = nullptr;
		ILoggingSystem* m_loggingSystem = nullptr;
		IInputSystem* m_inputSystem = nullptr;
		IWindowSystem* m_windowSystem = nullptr;
		IParsingSystem* m_parsingSystem = nullptr;
		IGeometrySystem* m_geometrySystem = nullptr;
		IMathSystem* m_mathSystem = nullptr;
		IRenderSystem* m_renderSystem = nullptr;

		//App
		HMODULE appDLL=NULL;
		typedef void (*initAppFunc)(LayerStack* layerstack);
	};
}//end namespace