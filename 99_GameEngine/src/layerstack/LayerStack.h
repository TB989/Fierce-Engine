#pragma once

#include "src/layers/LayerStack.h"
#include "src/systemManager/SystemManager.h"

#include <vector>

namespace Fierce {
	class LayerStack:public ILayerStack {
	public:
		LayerStack(SystemManager* manager);
		~LayerStack();

		void pushLayer(Layer* layer) override;
		void popLayer(Layer* layer) override;

	private:
		SystemManager* m_manager=nullptr;
		std::vector<Layer*> m_layers;
	};
}//end namespace