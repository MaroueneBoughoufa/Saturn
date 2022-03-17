include "./vendor/premake/premake_customization/solution_items.lua"
include "./vendor/premake/premake_customization/actions.lua"
include "dependencies.lua"

require "vendor/premake/premake_customization/workspaces/codeblocks/codeblocks"
require "vendor/premake/premake_customization/workspaces/vscode/vscode"

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

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Saturn/vendor/glfw"
	include "Saturn/vendor/glad"
	include "Saturn/vendor/imgui"
group ""

include "Saturn"
include "Sandbox"
