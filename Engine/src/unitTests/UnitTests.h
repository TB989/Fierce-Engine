#pragma once

#include "src/Common.h"

#include "src/core/Core.h"

#include "GeometryLibrary.h"

class Test_EngineConfig : public Core {
public:
	Test_EngineConfig();

protected:
	void init() override;
	void update() override;
	void doRender() override;
	void cleanUp() override;
};

class Test_GeometryLibrary : public Core {
public:
	Test_GeometryLibrary();

protected:
	void init() override;
	void update() override;
	void doRender() override;
	void cleanUp() override;

private:
	GeometryLoader* loader;
};