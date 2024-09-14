#pragma once

#include <vector>

namespace Fierce {

	class VK_CompatibilityCheck_Device;
	class ExtensionValidationLayerData;
	class DeviceData;
	class SurfaceData;

	class VK_CheckSupport {
	public:
		void addCheck(VK_CompatibilityCheck_Device* check);

	protected:
		bool doChecks(ExtensionValidationLayerData* data, DeviceData* deviceData, SurfaceData* surfaceData);

	protected:
		std::vector<VK_CompatibilityCheck_Device*> m_checks;
	};

}//end namespace