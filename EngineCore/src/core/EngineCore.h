#pragma once

#include "src/Logger.h"
#include "EngineSettings.h"
#include "src/WindowSystem.h"

namespace Fierce {

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
		Logger* m_logger=nullptr;

		static bool m_running;

		WindowSystem* m_windowSystem=nullptr;
		Window* m_window=nullptr;
	};

}//end namespace