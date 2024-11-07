#pragma once

#include "EngineSettings.h"

#include "src/renderSystem/RenderSystem.h"

namespace Fierce {

	class LoggingSystem;
	class Logger;
	class WindowSystem;

	class EngineCore {
	public:
		EngineCore();
		~EngineCore();

		void run();
		static void stop();

	public:
		virtual void init()=0;
		virtual void update()=0;
		virtual void render()=0;
		virtual void cleanUp()=0;

	private:
		void coreInit();
		void coreUpdate();
		void coreRender();
		void coreCleanUp();

	protected:
		EngineSettings m_settings = {};

	private:
		static bool m_running;

	protected:
		LoggingSystem* m_loggingSystem = nullptr;
		Logger* m_logger = nullptr;

		WindowSystem* m_windowSystem=nullptr;
		Window* m_window=nullptr;

		RenderSystem* m_renderSystem=nullptr;
	};

}//end namespace