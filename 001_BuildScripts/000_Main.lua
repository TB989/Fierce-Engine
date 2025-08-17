include "Dependencies.lua"

workspace "Fierce-Engine"
	architecture "x86_64"
	startproject "130_EngineCore"

	configurations { "Debug", "Release" }

	flags { "MultiProcessorCompile" }

	location "../"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	include "001_BuildScripts.lua"
	include "002_Assets.lua"
	include "100_PlatformLayer.lua"
	include "101_MathLibrary.lua"
	include "102_GeometryLibrary.lua"
	include "103_Parsers.lua"
	include "120_VulkanRenderer.lua"
	include "130_EngineCore.lua"
	include "121_GUI.lua"