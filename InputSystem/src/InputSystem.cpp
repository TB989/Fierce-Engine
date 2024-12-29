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

    void InputSystem::onKeyDown(BINDING binding){
        m_logger->info("Key down");
        auto it = m_actions.find(binding);
        if (it->second!=nullptr) {
            it->second->run();
        }
    }
}//end namespace