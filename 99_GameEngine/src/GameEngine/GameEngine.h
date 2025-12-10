#pragma once

#include "src/GameEngine/SystemManager.h"
#include "src/GameEngine/TestSystems.h"

namespace Fierce{
	class GameEngine{
	public:
		GameEngine();
		~GameEngine();

		void run();

	private:
		SystemManager* m_systemManager=nullptr;

		TestSystem1* system1;
		TestSystem2* system2;
		TestSystem3* system3;
	};
}//end namespace