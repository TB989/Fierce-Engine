IncludeDir = {}
IncludeDir["PlatformLayer"] = "%{wks.location}/100_PlatformLayer"
IncludeDir["Parsers"] = "%{wks.location}/101_Parsers"

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
Library["MathLibrary"] = "101_MathLibrary.lib"
Library["GeometryLibrary"] = "102_GeometryLibrary.lib"
Library["Parsers"] = "103_Parsers.lib"
Library["GUI"] = "104_GUI.lib"
Library["VulkanRenderer"] = "120_VulkanRenderer.lib"


Library["Vulkan"] = "vulkan-1.lib"