project "Logger"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/")
	objdir ("%{wks.location}/bin-int/")

	defines
	{
		WIN32_LEAN_AND_MEAN
	}

	files
	{
		"src/**.h",
		"src/**.cpp",
		"**.lua"
	}

	includedirs
	{
		"%{wks.location}/Logger/src",
		"%{IncludeDir.Utils}"
	}

	libdirs
	{

	}

	links
	{
		
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