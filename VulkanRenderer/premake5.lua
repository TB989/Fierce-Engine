project "VulkanRenderer"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/")
	objdir ("%{wks.location}/bin-int/")
	
	defines
	{
		"VK_USE_PLATFORM_WIN32_KHR",
		"DLL_EXPORT"
	}

	files
	{
		"src/**.h",
		"src/**.cpp",
		"premake5.lua",
		"%{IncludeDir.Common}/**.h"
	}

	includedirs
	{
		"../%{prj.name}/src",
		"%{IncludeDir.Common}",
		"%{IncludeDir.Vulkan}"
	}
	
	libdirs 
	{
		"%{LibraryDir.Common}",
		"%{LibraryDir.Vulkan}"
	}

	links 
	{
		"%{Library.Logger}",
		"%{Library.MathLibrary}",
		"%{Library.Vulkan}"
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "FIERCE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FIERCE_RELEASE"
		runtime "Release"
		optimize "on"