#pragma once

#include "../systems/IInputSystem.h"
#include "../systems/IRenderSystem.h"

#include "../systems/ISystemManager.h"

#include <string>

namespace Fierce {

    class Layer {
    public:
        explicit Layer(const std::string& name) : m_Name(name) {}
        virtual ~Layer() = default;

        virtual void OnAttach(ISystemManager* manager) {}
        virtual void OnDetach(ISystemManager* manager) {}
        virtual void OnInput(IInputSystem* inputSystem) {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender(IRenderSystem* renderSystem) {}
        virtual void OnRenderGUI() {}

        const std::string& GetName() const { return m_Name; }

    protected:
        std::string m_Name;
    };
}//end namespace