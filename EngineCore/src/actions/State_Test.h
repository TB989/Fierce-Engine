#pragma once

#include "src/Bindable.h"

namespace Fierce {
	class Logger;

	class State_Test :public State{
	public:
		State_Test(Logger* logger);

		void onStateChanged(bool isActivated) override;

	private:
		Logger* m_logger;
	};
}