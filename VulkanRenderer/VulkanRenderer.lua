project "VulkanRenderer"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/")
	objdir ("%{wks.location}/bin-int/")

	defines
	{
		
	}

	files
	{
		"src/**.h",
		"src/**.cpp",
		"**.lua"
	}

	includedirs
	{
		"%{wks.location}/VulkanRenderer/src",
		"%{IncludeDir.Logger}",
		"%{IncludeDir.Utils}",
		"%{IncludeDir.Vulkan}"
	}

	libdirs
	{
		"%{LibraryDir.Common}",
		"%{LibraryDir.Vulkan}"
	}

	links
	{
		"%{Library.Logger}",
		"%{Library.Vulkan}"
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