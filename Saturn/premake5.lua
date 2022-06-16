project "Saturn"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "stpch.h"
	pchsource "src/stpch.cpp"
	
	files {
		"src/Saturn.h",
		"src/stpch.cpp",
		"src/stpch.h",
		"src/Saturn/**.cpp",
		"src/Saturn/**.h",
		"src/Platform/OpenGL/**.cpp",
		"src/Platform/OpenGL/**.h",			
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
	}
	
	includedirs {
		"src",
		"vendor/spdlog/include",
		"vendor/glm",
		"vendor/glfw/include",
		"vendor/Glad/include",
		"vendor/imgui",
		"vendor/stb_image"
	}

	links {
		"glfw",
		"glad",
		"imgui",
		"opengl32.lib"
	}

	systemversion "latest"
	
	defines {
		"GLFW_INCLUDE_NONE",
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	filter "system:windows"		
		files {
			"src/Platform/Windows/**.cpp",
			"src/Platform/Windows/**.h",
		}
		

	filter "system:linux"		
		files {
			"src/Platform/Linux/**.cpp",
			"src/Platform/Linux/**.h",
		}

	filter "configurations:Debug"
		defines { "ST_DEBUG" }
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "ST_RELEASE"
		runtime "Release"
		optimize "on"
		symbols "on"

	filter "configurations:Dist"
		defines "ST_DIST"
		runtime "Release"
		optimize "on"
		symbols "off"
