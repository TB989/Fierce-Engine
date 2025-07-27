include "Dependencies.lua"

workspace "Fierce-Engine"
	architecture "x86_64"
	startproject "EngineCore"

	configurations { "Debug", "Release" }

	flags { "MultiProcessorCompile" }

	location "../"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	include "001_BuildScripts.lua"
	include "002_Assets.lua"
	include "100_PlatformLayer.lua"
	include "101_Parsers.lua"

	include "EngineCore.lua"
	include "VulkanRenderer.lua"
	include "MathLibrary.lua"
	include "GeometryLibrary.lua"
	include "GUI.lua"