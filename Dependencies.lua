IncludeDir = {}
IncludeDir["Logger"] = "%{wks.location}/Logger"
IncludeDir["Utils"] = "%{wks.location}/Utils"
IncludeDir["WindowSystem"] = "%{wks.location}/WindowSystem"
IncludeDir["Vulkan"] = "C:/VulkanSDK/1.3.290.0/Include"
IncludeDir["VulkanRenderer"] = "%{wks.location}/VulkanRenderer"

LibraryDir = {}
LibraryDir["Common"] = "%{wks.location}/bin"
LibraryDir["Vulkan"] = "C:/VulkanSDK/1.3.290.0/Lib"

Library = {}
Library["Logger"] = "Logger.lib"
Library["WindowSystem"] = "WindowSystem.lib"
Library["Vulkan"] = "vulkan-1.lib"
Library["VulkanRenderer"] = "VulkanRenderer.lib"