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
include "MathLibrary"
include "GeometryLibrary"
include "EntityComponentSystem"
include "EventSystem"
include "WindowSystem"
include "InputSystem"
include "RendererBase"
include "OpenGLRenderer"
include "VulkanRenderer"