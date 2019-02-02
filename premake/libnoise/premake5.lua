project "libnoise"
    location "../../lib/libnoise"
    kind "StaticLib"
    language "C++"

	targetdir ("%{prj.location}/build/bin/" .. outputDir .. "/%{prj.name}")
    objdir ("%{prj.location}/build/bin-obj/" .. outputDir .. "/%{prj.name}")

	files {
        "%{prj.location}/src/model/**.cpp",
        "%{prj.location}/src/module/**.cpp",
        "%{prj.location}/noiseutils/noiseutils.cpp"
    }

    includedirs {
        "%{prj.location}/src/",
        "%{prj.location}/src/noise",
        "%{prj.location}/noiseutils/"
    }

	filter "system:windows"
        buildoptions { "-std=c11", "-lgdi32" }
        systemversion "latest"
        staticruntime "On"

		defines {
            "_CRT_SECURE_NO_WARNINGS"
		}

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"

    filter "system:macosx"
        toolset "osx_gcc"
        xcodebuildsettings {
            ["HEADER_SEARCH_PATHS"] = "src/ src/noise/ noiseutils/"
        }
