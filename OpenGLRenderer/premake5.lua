project "OpenGLRenderer"
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
		"res/**.vs",
		"res/**.fs",
		"premake5.lua",
		"%{IncludeDir.Common}/**.h"
	}

	includedirs
	{
		"../%{prj.name}/src",
		"%{IncludeDir.Common}",
		"%{IncludeDir.External}"
	}
	
	libdirs 
	{
		"%{LibraryDir.Common}"
	}

	links 
	{
		"%{Library.OpenGL}",
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