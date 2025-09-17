project "121_GUI"
	kind "StaticLib"
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
		"%{IncludeDir.MathLibrary}",
		"%{IncludeDir.PlatformLayer}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.VulkanRenderer}"
	}

	libdirs
	{
		"%{LibraryDir.Common}"
	}

	links
	{
		"%{Library.MathLibrary}",
		"%{Library.PlatformLayer}",
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