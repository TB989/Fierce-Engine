#pragma once

#include "GUIPanel.h"

#include <vector>

namespace Fierce {
	class GUIContainer {
	protected:
		std::vector<GUIPanel> m_children;
	};
}