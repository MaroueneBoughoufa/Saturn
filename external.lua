outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Saturn Dependencies

IncludeDir = {}

IncludeDir["ImGui"] = "../Saturn/vendor/imgui"
IncludeDir["glm"] = "../Saturn/vendor/glm/glm"
IncludeDir["spdlog"] = "../Saturn/vendor/spdlog/include"

group "Dependencies"
	include "Saturn/vendor/glfw"
	include "Saturn/vendor/Glad"
	include "Saturn/vendor/imgui"
group ""

group "Core"
	include "Saturn"
group ""
