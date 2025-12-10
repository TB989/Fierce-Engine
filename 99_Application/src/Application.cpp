#include "src/Application.h"
#include <iostream>

namespace Fierce {

    Application::Application(const ApplicationSpecification& specification)
        : m_specification(specification) {
    }

    Application::~Application() {
        for (auto layer : m_layers) {
            layer->OnDetach();
            delete layer;
        }
        m_layers.clear();
    }

    void Application::pushLayer(Layer* layer) {
        m_layers.push_back(layer);
        layer->OnAttach();
    }

    void Application::run() {
        std::cout << "Running application: " << m_specification.name << "\n";
        const float dt = 1.0f / 60.0f;
        while (m_running) {
            for (auto layer : m_layers) {
                layer->OnUpdate(dt);
            }
            // stop after a single loop for demonstration
            m_running = false;
        }
        close();
    }

    void Application::close() {
        std::cout << "Application closed.\n";
        m_running = false;
    }
}