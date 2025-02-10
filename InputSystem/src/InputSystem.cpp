#include "InputSystem.h"

#include "InputContext.h"

#include "src/LoggingSystem.h"

namespace Fierce {

    void InputSystem::initSystem(){
        m_logger = m_loggingSystem->createLogger("INP", true, "ALL_LOGS");

        m_inputContext_raw = new InputContext(true);
        m_inputContext_normal = new InputContext(false);

        m_activeContext = m_inputContext_raw;
    }

    void InputSystem::addAction(BINDING binding, Action* action, bool rawInput) {
        if (rawInput) {
            m_inputContext_raw->addAction(binding,action);
        }
        else {
            m_inputContext_normal->addAction(binding, action);
        }
    }

    void InputSystem::removeAction(BINDING binding, bool rawInput) {
        if (rawInput) {
            m_inputContext_raw->removeAction(binding);
        }
        else {
            m_inputContext_normal->removeAction(binding);
        }
    }

    void InputSystem::addState(BINDING binding, State* state, bool rawInput) {
        if (rawInput) {
            m_inputContext_raw->addState(binding, state);
        }
        else {
            m_inputContext_normal->addState(binding, state);
        }
    }

    void InputSystem::removeState(BINDING binding, bool rawInput) {
        if (rawInput) {
            m_inputContext_raw->removeState(binding);
        }
        else {
            m_inputContext_normal->removeState(binding);
        }
    }

    void InputSystem::addRange(BINDING binding, Range* range, bool rawInput) {
        if (rawInput) {
            m_inputContext_raw->addRange(binding, range);
        }
        else {
            m_inputContext_normal->addRange(binding, range);
        }
    }

    void InputSystem::removeRange(BINDING binding, bool rawInput) {
        if (rawInput) {
            m_inputContext_raw->removeRange(binding);
        }
        else {
            m_inputContext_normal->removeRange(binding);
        }
    }

    void InputSystem::updateSystem(){

    }

    void InputSystem::cleanUpSystem(){
        delete m_inputContext_raw;
        delete m_inputContext_normal;
    }

    void InputSystem::switchMouseMode(bool rawMouse){
        if (rawMouse) {
            m_activeContext = m_inputContext_raw;
        }
        else {
            m_activeContext = m_inputContext_normal;
        }
    }

    InputSystem::InputSystem(LoggingSystem* loggingSystem){
        m_loggingSystem = loggingSystem;
    }

}//end namespace