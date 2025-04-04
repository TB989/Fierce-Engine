#pragma once

namespace Fierce {

	class System {
	public:
		virtual void initSystem() = 0;
		virtual void updateSystem() = 0;
		virtual void cleanUpSystem() = 0;
	};

}//end namespace