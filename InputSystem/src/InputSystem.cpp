#include "InputSystem.h"

#include "src/LoggingSystem.h"

namespace Fierce {

    void InputSystem::initSystem(){
        m_logger = m_loggingSystem->createLogger("INP", true, "ALL_LOGS");
    }

    void InputSystem::updateSystem(){

    }

    void InputSystem::cleanUpSystem(){

    }

    InputSystem::InputSystem(LoggingSystem* loggingSystem){
        m_loggingSystem = loggingSystem;
    }

    void InputSystem::addAction(BINDING binding, Action* action){
        m_actions.insert({binding,action});
    }

    void InputSystem::removeAction(BINDING binding){
        m_actions.erase(binding);
    }

    void InputSystem::addState(BINDING binding, State* state){
        m_states.insert({binding,state});
    }

    void InputSystem::removeState(BINDING binding){
        m_states.erase(binding);
    }

    void InputSystem::addRange(BINDING binding, Range* range){
        m_ranges.insert({binding,range});
    }

    void InputSystem::removeRange(BINDING binding){
        m_ranges.erase(binding);
    }

    void InputSystem::onKeyDown(BINDING binding){
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

    void InputSystem::onKeyUp(BINDING binding){
        auto it = m_states.find(binding);
        if (it != m_states.end()) {
            if (it->second != nullptr) {
                it->second->onStateChanged(false);
            }
        }
    }

    void InputSystem::onMouseMoveX(BINDING binding, int value){
        if (first) {
            first = false;
            m_mouseX = (float)value;
            return;
        }

        float delta = (float)value - m_mouseX;
        m_mouseX = (float)value;
        auto it = m_ranges.find(MOUSE_X_AXIS);
        if (it != m_ranges.end()) {
            if (it->second != nullptr) {
                it->second->onRangeChanged(delta);
            }
        }
    }

    void InputSystem::onMouseMoveY(BINDING binding, int value) {
        if (first) {
            first = false;
            m_mouseY = (float)value;
            return;
        }

        float delta = (float)value - m_mouseY;
        m_mouseY = (float)value;
        auto it = m_ranges.find(MOUSE_Y_AXIS);
        if (it != m_ranges.end()) {
            if (it->second != nullptr) {
                it->second->onRangeChanged(delta);
            }
        }
    }

    void InputSystem::onMouseWheelMove(BINDING binding, int value){
        auto it = m_ranges.find(binding);
        if (it!=m_ranges.end()) {
            if (it->second != nullptr) {
                it->second->onRangeChanged((float)value);
            }
        }
    }

    void InputSystem::onMouseKeyDown(BINDING binding){
        auto it = m_states.find(binding);
        if (it != m_states.end()) {
            if (it->second != nullptr) {
                it->second->onStateChanged(true);
            }
        }

        auto it2 = m_actions.find(binding);
        if (it2!=m_actions.end()) {
            if (it2->second != nullptr) {
                it2->second->onAction();
            }
        }
    }

    void InputSystem::onMouseKeyUp(BINDING binding){
        auto it = m_states.find(binding);
        if (it!=m_states.end()) {
            if (it->second != nullptr) {
                it->second->onStateChanged(false);
            }
        }
    }
}//end namespace