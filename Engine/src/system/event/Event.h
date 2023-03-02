#pragma once

#include "src/Common.h"

struct Event {};

//********** Keyboard events ******//
struct KeyDownEvent : public Event {
	KeyDownEvent(WPARAM key) :m_key{ key } {}
	WPARAM m_key;
};
struct KeyUpEvent : public Event {
	KeyUpEvent(WPARAM key) :m_key{ key } {}
	WPARAM m_key;
};
struct CharEvent : public Event {
	CharEvent(char character) :m_character{ character } {}
	char m_character;
};
//*********************************//

//********** Mouse events *********//
enum MOUSE_BUTTON {
	RIGHT,
	LEFT,
	MIDDLE
};
struct ButtonDownEvent : public Event {
	ButtonDownEvent(MOUSE_BUTTON button, int x, int y) :m_button{ button }, m_x{ x }, m_y{ y } {}
	MOUSE_BUTTON m_button;
	int m_x;
	int m_y;
};
struct ButtonUpEvent : public Event {
	ButtonUpEvent(MOUSE_BUTTON button, int x, int y) :m_button{ button }, m_x{ x }, m_y{ y } {}
	MOUSE_BUTTON m_button;
	int m_x;
	int m_y;
};
struct MouseMoveEvent : public Event {
	MouseMoveEvent(int x, int y) : m_x{ x }, m_y{ y } {}
	int m_x;
	int m_y;
};
struct MouseScrollEvent : public Event {
	MouseScrollEvent(int delta, int x, int y) : m_delta{ delta }, m_x{ x }, m_y{ y } {}
	int m_delta;
	int m_x;
	int m_y;
};