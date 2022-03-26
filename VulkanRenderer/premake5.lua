project "VulkanRenderer"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/")
	objdir ("%{wks.location}/bin-int/")
	
	defines
	{
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
		"%{IncludeDir.Common}"
	}
	
	libdirs 
	{
		"%{LibraryDir.Common}"
	}

	links 
	{
		"%{Library.Logger}"
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