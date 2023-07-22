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
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"premake5.lua",
		"res/**"
	}

	includedirs
	{
		"%{prj.location}",
		"%{wks.location}/external",
		"%{IncludeDir.Logger}",
		"%{IncludeDir.MathLibrary}",
		"%{IncludeDir.RendererBase}",
		"%{IncludeDir.GeometryLibrary}"
	}
	
	libdirs 
	{
		"%{LibraryDir.Common}"
	}

	links 
	{
		"%{Library.OpenGL}",
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