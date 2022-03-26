include "Dependencies.lua"

workspace "Fierce-Engine"
	architecture "x86_64"
	startproject "Engine"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

include "Engine"
include "Logger"
include "OpenGLRenderer"
include "VulkanRenderer"