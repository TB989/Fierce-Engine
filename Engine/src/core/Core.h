#pragma once

#include "EngineSettings.h"
#include "Logger.h"

#include "system/window/WindowSystem.h"

#include <Windows.h>
#include "DLLTest.h"

class Core {
private:
	void coreInit();
	void coreUpdate();
	void coreRender();
	void coreCleanUp();

	void loadRenderer();

	bool running = false;

protected:
	virtual void init()=0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void cleanUp()=0;

public:
	Core();
	~Core();

	void run();
	void stop() { running = false; }

public:
	static Logger* LOGGER;

	//Window system
	WindowSystem* windowSystem=nullptr;
	FierceWindow* dummyWindow=nullptr;
	FierceWindow* window=nullptr;

	//Renderer
	HINSTANCE m_renderer = NULL;
	PFN_INIT_RENDERER_PROC initRenderer = nullptr;
	PFN_RENDER_PROC doRender = nullptr;
	PFN_CLEAN_UP_RENDERER_PROC cleanUpRenderer = nullptr;

protected:
	EngineSettings m_settings = {};
};