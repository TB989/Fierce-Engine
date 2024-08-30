include "Dependencies.lua"

workspace "Fierce-Engine"
	architecture "x86_64"
	startproject "EngineCore"

	configurations { "Debug", "Release" }

	flags { "MultiProcessorCompile" }

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	include "EngineCore/EngineCore.lua"