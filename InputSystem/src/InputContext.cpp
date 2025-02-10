#include "InputContext.h"

namespace Fierce {
    InputContext::InputContext(bool acceptsRawMouseInput){
        m_acceptsRawMouseInput = acceptsRawMouseInput;
    }

    void InputContext::addAction(BINDING binding, Action* action) {
        m_actions.insert({ binding,action });
    }

    void InputContext::removeAction(BINDING binding) {
        m_actions.erase(binding);
    }

    void InputContext::addState(BINDING binding, State* state) {
        m_states.insert({ binding,state });
    }

    void InputContext::removeState(BINDING binding) {
        m_states.erase(binding);
    }

    void InputContext::addRange(BINDING binding, Range* range) {
        m_ranges.insert({ binding,range });
    }

    void InputContext::removeRange(BINDING binding) {
        m_ranges.erase(binding);
    }

    void InputContext::onKeyDown(BINDING binding) {
        auto it = m_states.find(binding);
        if (it != m_states.end()) {
            if (it->second != nullptr) {
                it->second->onStateChanged(true);
            }
        }

        auto it2 = m_actions.find(binding);
        if (it2 != m_actions.end()) {
            if (it2->second != nullptr) {
                it2->second->onAction();
            }
        }
    }

    void InputContext::onKeyUp(BINDING binding) {
        auto it = m_states.find(binding);
        if (it != m_states.end()) {
            if (it->second != nullptr) {
                it->second->onStateChanged(false);
            }
        }
    }

    void InputContext::onMouseMoveX(BINDING binding, int value) {
        auto it = m_ranges.find(MOUSE_X_AXIS);
        if (it != m_ranges.end()) {
            if (it->second != nullptr) {
                it->second->onRangeChanged((float)value);
            }
        }
    }

    void InputContext::onMouseMoveY(BINDING binding, int value) {
        auto it = m_ranges.find(MOUSE_Y_AXIS);
        if (it != m_ranges.end()) {
            if (it->second != nullptr) {
                it->second->onRangeChanged((float)value);
            }
        }
    }

    void InputContext::onMouseWheelMove(BINDING binding, int value) {
        auto it = m_ranges.find(binding);
        if (it != m_ranges.end()) {
            if (it->second != nullptr) {
                it->second->onRangeChanged((float)value);
            }
        }
    }

    void InputContext::onMouseKeyDown(BINDING binding) {
        auto it = m_states.find(binding);
        if (it != m_states.end()) {
            if (it->second != nullptr) {
                it->second->onStateChanged(true);
            }
        }

        auto it2 = m_actions.find(binding);
        if (it2 != m_actions.end()) {
            if (it2->second != nullptr) {
                it2->second->onAction();
            }
        }
    }

    void InputContext::onMouseKeyUp(BINDING binding) {
        auto it = m_states.find(binding);
        if (it != m_states.end()) {
            if (it->second != nullptr) {
                it->second->onStateChanged(false);
            }
        }
    }
}//end namespace