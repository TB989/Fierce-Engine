#include "VK_CheckSupport.h"

#include "VK_CompatibilityChecks.h"

namespace Fierce {

    void VK_CheckSupport::addCheck(VK_CompatibilityCheck_Device* check){
        m_checks.push_back(check);
    }

    bool VK_CheckSupport::doChecks(ExtensionValidationLayerData* data, DeviceData* deviceData, SurfaceData* surfaceData){
        for (auto mcheck : m_checks) {
            if (!mcheck->check(data, deviceData, surfaceData)) {
                return false;
            }
        }
        return true;
    }

}//end namespace