#include "VK_Check_System.h"

bool VK_Check_System::doCheck(ExtensionValidationLayerData* data, DeviceData* deviceData, SurfaceData* surfaceData){
    for (auto mcheck : checks) {
        if (!mcheck->check(data, deviceData, surfaceData)) {
            return false;
        }
    }

    return true;
}