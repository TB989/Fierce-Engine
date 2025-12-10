#include "Application.h"
#include <iostream>

namespace Fierce {
    Application::Application() {
        std::cout << "Engine started.\n";
    }

    Application::~Application() {
        std::cout << "Engine shutting down.\n";
    }

    void Application::Run() {
        while (m_Running) {
            for (auto& layer : m_Layers) {
                layer->OnUpdate(0.016f); // simulate 60fps
                layer->OnRender();
            }
            // For demo: stop after one loop
            m_Running = false;
        }
    }

    void Application::PushLayer(Layer* layer) {
        m_Layers.push_back(layer);
        layer->OnAttach();
    }

    void Application::PopLayer(Layer* layer) {
        layer->OnDetach();
    }
}//end namespace