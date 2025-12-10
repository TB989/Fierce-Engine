#pragma once
#include <vector>
#include "src/Layer.h"

namespace Fierce {
    class Application {
    public:
        Application();
        ~Application();

        void Run();
        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

    private:
        std::vector<Layer*> m_Layers;
        bool m_Running = true;
    };
}//end namespace