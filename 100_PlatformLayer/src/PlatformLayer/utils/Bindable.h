#pragma once

namespace Fierce {
	class Action {
	public:
		Action() {};
		virtual ~Action() {}

		virtual void onAction() = 0;
	};

	class State {
	public:
		State() {};
		virtual ~State() {}

		virtual void onStateChanged(bool isActive) = 0;
	};

	class Range {
	public:
		Range() {};
		virtual ~Range() {}

		virtual void onRangeChanged(float range1,float range2) = 0;
	};
}//end namespace