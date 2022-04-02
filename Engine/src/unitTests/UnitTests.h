#pragma once

#include "core/Core.h"

class Test_EngineConfig : public Core {
public:
	Test_EngineConfig();

protected:
	void init() override;
	void update() override;
	void render() override;
	void cleanUp() override;
};