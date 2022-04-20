IncludeDir = {}
IncludeDir["Common"] = "%{wks.location}/CommonIncludes"
IncludeDir["External"] = "%{wks.location}/external"
IncludeDir["Vulkan"] = "C:/VulkanSDK/1.2.135.0/Include"

LibraryDir = {}
LibraryDir["Common"] = "%{wks.location}/bin"
LibraryDir["Vulkan"] = "C:/VulkanSDK/1.2.135.0/Lib"

Library = {}
Library["Logger"] = "Logger.lib"
Library["OpenGL"] = "OpenGL32.lib"
Library["Vulkan"] = "vulkan-1.lib"