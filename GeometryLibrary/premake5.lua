project "GeometryLibrary"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/")
	objdir ("%{wks.location}/bin-int/")
	
	defines
	{
		
	}

	files
	{
		"src/**.h",
		"src/**.cpp",
		"premake5.lua"
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