#pragma once

#include "src/GameEngine/SystemManager.h"
#include "src/PlatformLayer/include/Plattform.h"

namespace Fierce{
	class GameEngine{
	public:
		GameEngine();
		~GameEngine();

		void run();

	private:
		SystemManager* m_systemManager=nullptr;
		Plattform* m_plattform = nullptr;

		ITimeDateSystem* m_timeDateSystem=nullptr;
	};
}//end namespace