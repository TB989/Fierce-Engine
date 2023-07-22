project "WindowSystem"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/")
	objdir ("%{wks.location}/bin-int/")
	
	defines
	{
		"WIN32_LEAN_AND_MEAN",
		"NOMINMAX"
	}

	files
	{
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"premake5.lua"
	}

	includedirs
	{
		"%{prj.location}",
		"%{IncludeDir.Logger}",
		"%{IncludeDir.InputSystem}"
	}
	
	libdirs 
	{
		"%{Library.Logger}"
	}

	links 
	{
		
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