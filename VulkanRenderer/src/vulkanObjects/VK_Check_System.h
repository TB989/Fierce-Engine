#pragma once

#include "src/Common.h"
#include "VulkanObject.h"

#include "VK_CompatibilityChecks.h"

class VK_Check_System {
public:
	void addCheck(VK_CompatibilityCheck* check) { checks.push_back(check); }
protected:
	bool doCheck(ExtensionValidationLayerData* data, DeviceData* deviceData, SurfaceData* surfaceData);
private:
	std::vector<VK_CompatibilityCheck*> checks;
};