#pragma once

namespace Fierce {
	class Action {
	public:
		virtual ~Action() = default;
		virtual void onAction() = 0;
	};

	class State {
	public:
		virtual ~State() = default;
		virtual void onStateChanged(bool isActive) = 0;
	};

	class Range {
	public:
		virtual ~Range() = default;
		virtual void onRangeChanged(float range1,float range2) = 0;
	};
}//end namespace