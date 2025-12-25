#include "src/layers/LayerStack.h"

#include "src/layers/Layer2D.h"
#include "src/layers/Layer3D.h"

namespace Fierce {
	extern "C" __declspec(dllexport) void initApp(ILayerStack* layerStack) {
		//TODO: Who deletes the layers???

		layerStack->pushLayer(new Layer2D());
		layerStack->pushLayer(new Layer3D());
	}
}//end namespace