project "InputSystem"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/")
	objdir ("%{wks.location}/bin-int/")

	dependson ("Logger")	

	defines
	{
		
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
		"%{IncludeDir.Logger}"
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