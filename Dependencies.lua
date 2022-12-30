IncludeDir = {}
IncludeDir["Common"] = "%{wks.location}/CommonIncludes"
IncludeDir["External"] = "%{wks.location}/external"
IncludeDir["Vulkan"] = "C:/VulkanSDK/1.3.216.0/Include"

LibraryDir = {}
LibraryDir["Common"] = "%{wks.location}/bin"
LibraryDir["Vulkan"] = "C:/VulkanSDK/1.3.216.0/Lib"

Library = {}
Library["Logger"] = "Logger.lib"
Library["MathLibrary"] = "MathLibrary.lib"
Library["GeometryLibrary"] = "GeometryLibrary.lib"
Library["OpenGL"] = "OpenGL32.lib"
Library["Vulkan"] = "vulkan-1.lib"