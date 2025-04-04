project "EngineCore"
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
		"%{wks.location}/%{prj.name}/src/**.cpp",
		"%{wks.location}/%{prj.name}/**.ini"
	}

	includedirs
	{
		"%{wks.location}/%{prj.name}",
		"%{IncludeDir.PlatformLayer}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.VulkanRenderer}",
		"%{IncludeDir.MathLibrary}",
		"%{IncludeDir.GeometryLibrary}",
		"%{IncludeDir.GUI}"
	}

	libdirs 
	{
		"%{LibraryDir.Common}"
	}

	links
	{
		"%{Library.PlatformLayer}",
		"%{Library.VulkanRenderer}",
		"%{Library.MathLibrary}",
		"%{Library.GeometryLibrary}"
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