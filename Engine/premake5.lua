project "Engine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/")
	objdir ("%{wks.location}/bin-int/")
	
	defines
	{
		"WIN32_LEAN_AND_MEAN",
		"NOMINMAX",
		"DLL_IMPORT"
	}

	files
	{
		"src/**.h",
		"src/**.cpp",
		"premake5.lua",
		"Engine.ini",
		"%{IncludeDir.Common}/**.h"
	}

	includedirs
	{
		"../%{prj.name}/src",
		"%{IncludeDir.Common}"
	}
	
	libdirs 
	{
		"%{LibraryDir.Common}"
	}

	links 
	{
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