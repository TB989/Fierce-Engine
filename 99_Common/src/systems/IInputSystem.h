#pragma once

#include "System.h"

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
        virtual void onRangeChanged(float range1, float range2) = 0;
    };

    enum BINDING {
        //Mouse
        MOUSE_MOVE,
        MOUSE_WHEEL_MOVE,
        MOUSE_BUTTON_LEFT,
        MOUSE_BUTTON_MIDDLE,
        MOUSE_BUTTON_RIGHT,

        // Function keys
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

        // Alphanumeric keys
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

        // Numeric keys
        KEY_0,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,

        // Control keys
        KEY_ESC,
        KEY_TAB,
        KEY_SHIFT,
        KEY_CTRL,
        KEY_ALT,
        KEY_ENTER,
        KEY_BACKSPACE,
        KEY_SPACE,

        // Arrow keys
        KEY_LEFT,
        KEY_UP,
        KEY_RIGHT,
        KEY_DOWN,

        // Special keys
        KEY_INSERT,
        KEY_DELETE,
        KEY_HOME,
        KEY_END,
        KEY_PAGE_UP,
        KEY_PAGE_DOWN,

        // Numeric keypad
        KEY_NUMPAD0,
        KEY_NUMPAD1,
        KEY_NUMPAD2,
        KEY_NUMPAD3,
        KEY_NUMPAD4,
        KEY_NUMPAD5,
        KEY_NUMPAD6,
        KEY_NUMPAD7,
        KEY_NUMPAD8,
        KEY_NUMPAD9,
        KEY_NUMPAD_PLUS,
        KEY_NUMPAD_MINUS,
        KEY_NUMPAD_MULTIPLY,
        KEY_NUMPAD_DIVIDE,
        KEY_NUMPAD_DECIMAL
    };

    class InputContext;
    class IWindow;

	class IInputSystem:public System{
	public:
        virtual ~IInputSystem() = default;

		virtual void switchMouseMode(IWindow* window,bool rawMouse)=0;
        virtual InputContext* getActiveContext() = 0;

		virtual void addAction(BINDING binding, Action* action, bool rawInput)=0;
		virtual void removeAction(BINDING binding, bool rawInput)=0;

		virtual void addState(BINDING binding, State* state, bool rawInput)=0;
		virtual void removeState(BINDING binding, bool rawInput)=0;

		virtual void addRange(BINDING binding, Range* range, bool rawInput)=0;
		virtual void removeRange(BINDING binding, bool rawInput)=0;
	};
}//end namespace
