outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Saturn Dependencies

IncludeDir = {}

IncludeDir["GLFW"] = "%{wks.location}/Saturn/vendor/glfw/include"
IncludeDir["Glad"] = "%{wks.location}/Saturn/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Saturn/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Saturn/vendor/glm"
IncludeDir["spdlog"] = "%{wks.location}/Saturn/vendor/spdlog/include"
IncludeDir["stb"] = "%{wks.location}/Saturn/vendor/stb_image"


group "Dependencies"
	include "Saturn/vendor/glfw"
	include "Saturn/vendor/Glad"
	include "Saturn/vendor/imgui"
group ""

group "Core"
	include "Saturn"
group ""
