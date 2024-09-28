include "Dependencies.lua"

workspace "Fierce-Engine"
	architecture "x86_64"
	startproject "EngineCore"

	configurations { "Debug", "Release" }

	flags { "MultiProcessorCompile" }

	location "../"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	include "BuildScripts.lua"
	include "EngineCore.lua"
	include "Logger.lua"
	include "Utils.lua"
	include "WindowSystem.lua"
	include "VulkanRenderer.lua"
	include "Shaders.lua"
	include "MathLibrary.lua"