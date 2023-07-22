#pragma once

#include "WindowSystem.h"
#include "EventSystem.h"
#include "InputSystem.h"

#include "src/Common.h"

#include "EngineSettings.h"
#include "src/system/renderer/FunctionLoader.h"

class Core {
private:
	void coreInit();
	void coreUpdate();
	void coreRender();
	void coreCleanUp();

	void onWindowClosed(WindowCloseEvent* event);
	void onKeyDown(KeyDownEvent* event);

	void loadRenderer();

	bool running = false;

protected:
	virtual void init()=0;
	virtual void update() = 0;
	virtual void doRender() = 0;
	virtual void cleanUp()=0;

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

	//Event system
	EventSystem* eventSystem=nullptr;

	//InputSystem
	InputSystem* inputSystem = nullptr;

	//Renderer
	HINSTANCE m_renderer = NULL;

protected:
	EngineSettings m_settings = {};
};