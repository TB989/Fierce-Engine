#include "src/layers/LayerStack.h"
#include "LayerStack.h"

namespace Fierce{

    LayerStack::LayerStack(SystemManager* manager){
        m_manager = manager;
    }

    LayerStack::~LayerStack(){
        for (Layer* layer:m_layers) {
            layer->OnDetach(m_manager);
            delete layer;
        }
    }

    void Fierce::LayerStack::pushLayer(Layer* layer){
        layer->OnAttach(m_manager);
        m_layers.push_back(layer);
    }

    void LayerStack::popLayer(Layer* layer){
        auto it = std::find(m_layers.begin(), m_layers.begin(),layer);
        if (it != m_layers.end()){
            (*it)->OnDetach(m_manager);
            m_layers.erase(it);
        }
    }
}//end namespace