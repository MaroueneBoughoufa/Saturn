include "./vendor/premake/premake_customization/solution_items.lua"
include "./vendor/premake/premake_customization/actions.lua"

workspace "SaturnEngine"
	architecture "x86_64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	solution_items {
		".editorconfig"
	}

	flags {
		"MultiProcessorCompile"
	}

include "external.lua"
include "Sandbox"