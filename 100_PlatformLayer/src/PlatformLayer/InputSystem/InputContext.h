#pragma once

#include <unordered_map>

#include "src/systems/IInputSystem.h"

namespace Fierce {
	class InputContext{
	public:
		InputContext(bool acceptsRawMouseInput);

		bool acceptsRawMouseInput();

		void addAction(BINDING binding, Action* action);
		void removeAction(BINDING binding);

		void addState(BINDING binding, State* state);
		void removeState(BINDING binding);

		void addRange(BINDING binding, Range* range);
		void removeRange(BINDING binding);

		void onKeyDown(BINDING binding);
		void onKeyUp(BINDING binding);
		void onMouseMoved(BINDING binding, int x, int y);
		void onMouseWheelMove(BINDING binding, int value);
		void onMouseKeyDown(BINDING binding);
		void onMouseKeyUp(BINDING binding);

	private:
		bool m_acceptsRawMouseInput = false;
		std::unordered_map<BINDING, Action*> m_actions;
		std::unordered_map<BINDING, State*> m_states;
		std::unordered_map<BINDING, Range*> m_ranges;
	};
}//end namespace