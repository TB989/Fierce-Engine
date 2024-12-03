project "VulkanRenderer"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	location "%{wks.location}/%{prj.name}/"

	targetdir ("%{wks.location}/bin/")
	objdir ("%{wks.location}/bin-int/")

	defines
	{
		"WIN32_LEAN_AND_MEAN",
		"NOMINMAX",
		"VK_USE_PLATFORM_WIN32_KHR"
	}

	files
	{
		"%{wks.location}/%{prj.name}/src/**.h",
		"%{wks.location}/%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/%{prj.name}",
		"%{IncludeDir.Logger}",
		"%{IncludeDir.Utils}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.MathLibrary}",

		"C:/Users/tmbal/Downloads/glfw-3.4.bin.WIN64/glfw-3.4.bin.WIN64/include",
		"C:/Users/tmbal/Desktop/Fierce-Engine/extern/glm"
	}

	libdirs
	{
		"%{LibraryDir.Common}",
		"%{LibraryDir.Vulkan}",

		"C:/Users/tmbal/Downloads/glfw-3.4.bin.WIN64/glfw-3.4.bin.WIN64/lib-vc2022"
	}

	links
	{
		"%{Library.Logger}",
		"%{Library.Vulkan}",
		"%{Library.MathLibrary}",

		"glfw3.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "FE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FE_RELEASE"
		runtime "Release"
		optimize "on"