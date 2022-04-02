#pragma once

#include "EngineSettings.h"
#include "Logger.h"

class Core {
private:
	void coreInit();
	void coreUpdate();
	void coreRender();
	void coreCleanUp();

protected:
	virtual void init()=0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void cleanUp()=0;

public:
	Core();
	~Core();

	void run();

public:
	static Logger* LOGGER;

private:
	EngineSettings m_settings = {};
	
};