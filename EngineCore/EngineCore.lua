project "EngineCore"
	kind "ConsoleApp"
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
		"**.lua",
		"**.ini"
	}

	includedirs
	{
		"%{wks.location}/EngineCore/src",
		"%{IncludeDir.Logger}",
		"%{IncludeDir.Utils}",
		"%{IncludeDir.WindowSystem}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.VulkanRenderer}"
	}

	libdirs 
	{
		"%{LibraryDir.Common}"
	}

	links
	{
		"%{Library.Logger}",
		"%{Library.WindowSystem}",
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