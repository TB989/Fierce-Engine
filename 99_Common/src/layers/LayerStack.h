#pragma once

#include "Layer.h"

namespace Fierce {
    class ILayerStack {
    public:
        virtual ~ILayerStack() = default;

        virtual void pushLayer(Layer* layer) = 0;
        virtual void popLayer(Layer* layer) = 0;
    };
}//end namespace