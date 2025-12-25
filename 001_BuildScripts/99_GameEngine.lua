project "99_GameEngine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	location "%{wks.location}/%{prj.name}/"

	targetdir ("%{wks.location}/bin/")
	objdir ("%{wks.location}/bin-int/")

	defines
	{
		
	}

	files
	{
		"%{wks.location}/%{prj.name}/src/**.h",
		"%{wks.location}/%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/%{prj.name}",
		"%{IncludeDir.Common}",
		"%{IncludeDir.PlatformLayer}",
		"%{IncludeDir.Parsers}",
		"%{IncludeDir.GeometryLibrary}",
		"%{IncludeDir.MathLibrary}",
		"%{IncludeDir.VulkanRenderer}"
	}

	libdirs 
	{
		"%{LibraryDir.Common}"
	}

	links
	{
		"%{Library.PlatformLayer}",
		"%{Library.Parsers}",
		"%{Library.GeometryLibrary}",
		"%{Library.MathLibrary}",
		"%{Library.VulkanRenderer}"
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