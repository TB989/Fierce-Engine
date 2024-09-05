#pragma once

#include "core/EngineCore.h"
#include "src/vulkanObjects/VK_Instance.h"

namespace Fierce {

	class TestWindow : public EngineCore {
	public:
		TestWindow();
		~TestWindow();

		void init() override;
		void update() override;
		void render() override;
		void cleanUp() override;

	private:
		VK_Instance* m_instance;
	};

}//end namespace