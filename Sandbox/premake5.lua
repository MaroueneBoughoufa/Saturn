project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"src/**.h",
		"src/**.hpp",
		"src/**.c",
		"src/**.cpp",
	}
	
	includedirs {
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"../Saturn/vendor",
		"../Saturn/src"
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