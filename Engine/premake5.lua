project "Engine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/")
	objdir ("%{wks.location}/bin-int/")

	dependson ("Logger","MathLibrary","WindowSystem","GeometryLibrary")

	dpiawareness "High"
	
	defines
	{
		"DLL_IMPORT"
	}

	files
	{
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"premake5.lua",
		"Engine.ini",
		"res/**"
	}

	includedirs
	{
		"%{prj.location}",
		"%{IncludeDir.GeometryLibrary}",
		"%{IncludeDir.Logger}",
		"%{IncludeDir.MathLibrary}",
		"%{IncludeDir.WindowSystem}",
		"%{IncludeDir.RendererBase}",
		"%{IncludeDir.EventSystem}",
		"%{IncludeDir.InputSystem}",
		"%{IncludeDir.EntityComponentSystem}",
		"%{wks.location}/external/entt/src/entt"
	}
	
	libdirs 
	{
		"%{LibraryDir.Common}"
	}

	links 
	{
		"%{Library.GeometryLibrary}",
		"%{Library.Logger}",
		"%{Library.MathLibrary}",
		"%{Library.WindowSystem}"
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