#pragma once

#include <string>

#include "System.h"

namespace Fierce {
	class ISystemManager {
	public:
		virtual ~ISystemManager() = default;

		virtual System* getSystem(std::string name) = 0;
	};
}//end namespace