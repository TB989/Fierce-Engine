IncludeDir = {}
IncludeDir["PlatformLayer"] = "%{wks.location}/100_PlatformLayer"
IncludeDir["MathLibrary"] = "%{wks.location}/101_MathLibrary"
IncludeDir["GeometryLibrary"] = "%{wks.location}/102_GeometryLibrary"
IncludeDir["Parsers"] = "%{wks.location}/103_Parsers"
IncludeDir["GUI"] = "%{wks.location}/121_GUI"
IncludeDir["VulkanRenderer"] = "%{wks.location}/120_VulkanRenderer"

IncludeDir["Vulkan"] = "C:/VulkanSDK/1.3.290.0/Include"

LibraryDir = {}
LibraryDir["Common"] = "%{wks.location}/bin"
LibraryDir["Vulkan"] = "C:/VulkanSDK/1.3.290.0/Lib"

Library = {}
Library["PlatformLayer"] = "100_PlatformLayer.lib"
Library["MathLibrary"] = "101_MathLibrary.lib"
Library["GeometryLibrary"] = "102_GeometryLibrary.lib"
Library["Parsers"] = "103_Parsers.lib"
Library["GUI"] = "121_GUI.lib"
Library["VulkanRenderer"] = "120_VulkanRenderer.lib"

Library["Vulkan"] = "vulkan-1.lib"