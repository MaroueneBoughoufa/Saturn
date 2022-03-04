workspace "SaturnEngine"
	architecture "x64"
	startproject "Sandbox"
	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to the root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = "Saturn/vendor/spdlog/include"
IncludeDir["glm"] = "Saturn/vendor/glm"
IncludeDir["GLFW"] = "Saturn/vendor/glfw/include"
IncludeDir["Glad"] = "Saturn/vendor/glad/include"
IncludeDir["ImGui"] = "Saturn/vendor/imgui"

group "Dependencies"
	include "Saturn/vendor/glfw"
	include "Saturn/vendor/glad"
	include "Saturn/vendor/imgui"
group ""

project "Saturn"
	location "Saturn"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "stpch.h"
	pchsource "%{prj.name}/src/stpch.cpp"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}
	
	includedirs {
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links {
		"glfw",
		"glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"ST_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "system:linux"
		systemversion "latest"

		defines {
			"ST_PLATFORM_LINUX",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines {
			"ST_DEBUG",
			"ST_ENABLE_ASSERT"
		}
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "ST_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ST_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs {
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"Saturn/vendor",
		"Saturn/src"
	}

	links {
		"Saturn"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"ST_PLATFORM_WINDOWS"
		}

	filter "system:linux"
		systemversion "latest"

		defines {
			"ST_PLATFORM_LINUX"
		}

	filter "configurations:Debug"
		defines "ST_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "ST_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ST_DIST"
		runtime "Release"
		optimize "on"

newaction {
	trigger = "delete",
	description = "Remove all binaries and intermediate binaries, and project files.",
	execute = function()
		print("Removing binaries...")
		os.rmdir("./bin")
		print("Removing intermediate binaries...")
		os.rmdir("./bin-int")
		print("Removing project files...")
		os.rmdir("./.vs")
		os.remove("**Makefile")
		os.remove("**.mk")
		os.remove("**.workspace")
		os.remove("**.project")
		os.remove("**.sln")
		os.remove("**.vcxproj")
		os.remove("**.vcxproj.filters")
		os.remove("**.vcxproj.user")
		print("Done.")
	end
}

newaction {
	trigger = "clean",
	description = "Remove all binaries and intermediate binaries, and project files.",
	execute = function()
		print("Removing binaries...")
		os.rmdir("./bin")
		print("Removing intermediate binaries...")
		os.rmdir("./bin-int")
		print("Done.")
	end
}
