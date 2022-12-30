#pragma once

#include "Common.h"

#include "core/Core.h"
#include "Renderer_API.h"

class Test_EngineConfig : public Core {
public:
	Test_EngineConfig();

protected:
	void init() override;
	void update() override;
	void doRender() override;
	void cleanUp() override;

	void loadShaders() override;
	void loadPipelines() override;
	void loadRenderpass() override;
	void loadFramebuffers() override;
};