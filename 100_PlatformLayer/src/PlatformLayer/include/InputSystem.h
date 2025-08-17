#pragma once

#include <unordered_map>

#include "LoggingSystem.h"

#include "src/PlatformLayer/utils/System.h"
#include "src/PlatformLayer/utils/Bindable.h"

namespace Fierce {

    enum BINDING {
        //Mouse
        MOUSE_X_AXIS,
        MOUSE_Y_AXIS,
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
        bool m_acceptsRawMouseInput = false;
        std::unordered_map<BINDING, Action*> m_actions;
        std::unordered_map<BINDING, State*> m_states;
        std::unordered_map<BINDING, Range*> m_ranges;
    };

	class InputSystem :public System {
	public:
		void initSystem(std::string m_assetDirectory) override;
        void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;

		void switchMouseMode(bool rawMouse);
		InputContext* getActiveContext() { return m_activeContext; }

	public:
		InputSystem();

		void addAction(BINDING binding, Action* action, bool rawInput);
		void removeAction(BINDING binding, bool rawInput);

		void addState(BINDING binding, State* state, bool rawInput);
		void removeState(BINDING binding, bool rawInput);

		void addRange(BINDING binding, Range* range, bool rawInput);
		void removeRange(BINDING binding, bool rawInput);

	private:
		LoggingSystem* m_loggingSystem = nullptr;
		Logger* m_logger = nullptr;

		InputContext* m_inputContext_raw = nullptr;
		InputContext* m_inputContext_normal = nullptr;

		InputContext* m_activeContext = nullptr;
	};
}//end namespace
