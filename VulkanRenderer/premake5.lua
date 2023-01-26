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
		"**.h",
		"**.cpp",
		"premake5.lua"
	}

	includedirs
	{
		"../%{prj.name}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.Logger}",
		"%{IncludeDir.MathLibrary}"
	}
	
	libdirs 
	{
		"%{LibraryDir.Vulkan}",
		"%{LibraryDir.Common}"
	}

	links 
	{
		"%{Library.Vulkan}",
		"%{Library.Logger}",
		"%{Library.MathLibrary}"
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