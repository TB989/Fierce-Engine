#pragma once

#include "src/Logging.h"

#include <map>

enum class MAPPING {
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,

	KEY_ESC,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,

	KEY_TAB,
	KEY_ENTER,
	KEY_SPACE,
	KEY_SHIFT,

	MOUSE_WHEEL,
	MOUSE_AXIS_LR,
	MOUSE_AXIS_UD,

	MOUSE_BUTTON_RIGHT,
	MOUSE_BUTTON_LEFT,
	MOUSE_BUTTON_MIDDLE,

	NONE
};

class Action {
public:
	virtual void doAction(float dd)=0;
};

class InputSystem {
public:
	void addAction(MAPPING mapping, Action* action) { 
		mappings.insert({ mapping, action });
	};

	void fireAction(MAPPING mapping,float dd) {
		std::map<MAPPING, Action*>::iterator it;
		it = mappings.find(mapping);
		if (it != mappings.end()) {
			it->second->doAction(dd);
		}
	};

private:
	std::map<MAPPING, Action*> mappings;
};