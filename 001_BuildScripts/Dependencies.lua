IncludeDir = {}
IncludeDir["PlatformLayer"] = "%{wks.location}/100_PlatformLayer"

IncludeDir["Vulkan"] = "C:/VulkanSDK/1.3.290.0/Include"
IncludeDir["VulkanRenderer"] = "%{wks.location}/VulkanRenderer"
IncludeDir["MathLibrary"] = "%{wks.location}/MathLibrary"
IncludeDir["GeometryLibrary"] = "%{wks.location}/GeometryLibrary"
IncludeDir["GUI"] = "%{wks.location}/GUI"

LibraryDir = {}
LibraryDir["Common"] = "%{wks.location}/bin"
LibraryDir["Vulkan"] = "C:/VulkanSDK/1.3.290.0/Lib"

Library = {}
Library["PlatformLayer"] = "100_PlatformLayer.lib"

Library["Vulkan"] = "vulkan-1.lib"
Library["VulkanRenderer"] = "VulkanRenderer.lib"
Library["MathLibrary"] = "MathLibrary.lib"
Library["GeometryLibrary"] = "GeometryLibrary.lib"
Library["GUI"] = "GUI.lib"