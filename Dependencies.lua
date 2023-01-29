IncludeDir = {}
IncludeDir["Vulkan"] = "C:/VulkanSDK/1.3.216.0/Include"
IncludeDir["External"] = "%{wks.location}/external"
IncludeDir["Engine"] = "%{wks.location}/Engine"
IncludeDir["EntityComponentSystem"] = "%{wks.location}/EntityComponentSystem"
IncludeDir["GeometryLibrary"] = "%{wks.location}/GeometryLibrary"
IncludeDir["Logger"] = "%{wks.location}/Logger"
IncludeDir["MathLibrary"] = "%{wks.location}/MathLibrary"
IncludeDir["RendererBase"] = "%{wks.location}/RendererBase"
IncludeDir["OpenGLRenderer"] = "%{wks.location}/OpenGLRenderer"
IncludeDir["VulkanRenderer"] = "%{wks.location}/VulkanRenderer"

LibraryDir = {}
LibraryDir["Vulkan"] = "C:/VulkanSDK/1.3.216.0/Lib"
LibraryDir["Common"] = "%{wks.location}/bin"

Library = {}
Library["Vulkan"] = "vulkan-1.lib"
Library["OpenGL"] = "OpenGL32.lib"
Library["GeometryLibrary"] = "GeometryLibrary.lib"
Library["Logger"] = "Logger.lib"
Library["MathLibrary"] = "MathLibrary.lib"