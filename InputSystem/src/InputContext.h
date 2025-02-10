#pragma once

#include "src/Bindable.h"
#include "InputBindings.h"

#include <unordered_map>

namespace Fierce {
	class InputContext {
	public:
		InputContext(bool acceptsRawMouseInput);

		bool acceptsRawMouseInput() { return m_acceptsRawMouseInput; }

	public:
		void addAction(BINDING binding, Action* action);
		void removeAction(BINDING binding);

		void addState(BINDING binding, State* state);
		void removeState(BINDING binding);

		void addRange(BINDING binding, Range* range);
		void removeRange(BINDING binding);

	public:
		void onKeyDown(BINDING binding);
		void onKeyUp(BINDING binding);

		void onMouseMoveX(BINDING binding, int value);
		void onMouseMoveY(BINDING binding, int value);
		void onMouseWheelMove(BINDING binding, int value);
		void onMouseKeyDown(BINDING binding);
		void onMouseKeyUp(BINDING binding);

	private:
		bool m_acceptsRawMouseInput=false;
		std::unordered_map<BINDING, Action*> m_actions;
		std::unordered_map<BINDING, State*> m_states;
		std::unordered_map<BINDING, Range*> m_ranges;
	};
}//end namespace