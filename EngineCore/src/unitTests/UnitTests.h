#pragma once

#include "core/EngineCore.h"

namespace Fierce {

	class TestWindow : public EngineCore {
	public:
		TestWindow();
		~TestWindow();

		void init() override;
		void update() override;
		void render() override;
		void cleanUp() override;
	};

}//end namespace