#pragma once

#include "src/Common.h"

#include "EngineSettings.h"
#include "src/system/window/WindowSystem.h"
#include "src/system/renderer/FunctionLoader.h"

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
	virtual void doRender() = 0;
	virtual void cleanUp()=0;

	virtual void loadRenderpass() = 0;
	virtual void loadShaders() = 0;
	virtual void loadPipelines() = 0;
	virtual void loadFramebuffers() = 0;

public:
	Core();
	~Core();

	void run();
	void stop() { running = false; }

public:

	//Window system
	WindowSystem* windowSystem=nullptr;
	FierceWindow* dummyWindow=nullptr;
	FierceWindow* window=nullptr;

	//Renderer
	HINSTANCE m_renderer = NULL;

protected:
	EngineSettings m_settings = {};
};