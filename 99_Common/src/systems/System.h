#pragma once

#include <string>

namespace Fierce {
	class System {
	public:
		virtual void initSystem(std::string assetDirectory) = 0;
		virtual void linkSystem(System* system) = 0;
		virtual void updateSystem() = 0;
		virtual void cleanUpSystem() = 0;
	};
}//end namespace