workspace "Raider"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "lib/glfw/include"
IncludeDir["GLEW"] = "lib/glew/include"
IncludeDir["spdlog"] = "lib/spdlog/include"
IncludeDir["glm"] = "lib/glm"
IncludeDir["libnoise"] = "lib/libnoise/src"
IncludeDir["noiseutils"] = "lib/libnoise/noiseutils"
IncludeDir["stb"] = "lib/stb"
IncludeDir["imgui"] = "lib/imgui"

include "lib/glfw"
include "lib/glew"
include "lib/libnoise"
include "lib/imgui"

project "RaiderEngine"
	location "RaiderEngine"
	kind "SharedLib"
	language "C++"

	targetdir("build/bin/"..outputDir.."/%{prj.name}")
	objdir("build/bin-obj/"..outputDir.."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.imgui}",
		"%{prj.name}/src"
	}

	links
	{
		"GLFW",
		"GLEW",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions "/MD"

	defines
	{
		"RD_PLATFORM_WINDOWS",
		"RD_BUILD_DLL",
		"RD_DEBUG",
		"RD_ENABLE_ASSERTS"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../data"),
	}

	filter "configurations:Debug"
		defines "RD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RD_RELEASE"
		optimize "On"

project "RaiderCraft"
	location "RaiderCraft"
	kind "ConsoleApp"
	language "C++"
	debugdir "data"

	targetdir("build/bin/"..outputDir.."/%{prj.name}")
	objdir("build/bin-obj/"..outputDir.."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"RaiderEngine/src",
		"%{IncludeDir.stb}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.libnoise}",
		"%{IncludeDir.noiseutils}"
	}

	links
	{
		"GLEW",
		"GLFW",
		"libnoise",
		"opengl32.lib",
		"RaiderEngine"
	}

	defines
	{
		"RD_ENABLE_ASSERTS"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions "/MD"

		defines
		{
			"RD_PLATFORM_WINDOWS",
			"NOISE_STATIC"
		}

	filter "configurations:Debug"
		defines "RD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RD_RELEASE"
		optimize "On"
