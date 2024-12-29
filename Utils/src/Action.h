#pragma once

namespace Fierce {
	class Action {
	public:
		Action() {};
		virtual ~Action() {}

		virtual void run() = 0;
	};
}//end namespace