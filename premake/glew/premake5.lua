project "GLEW"
    location "../../lib/glew"
    kind "StaticLib"
    language "C"

	targetdir ("%{prj.location}/build/bin/" .. outputDir .. "/%{prj.name}")
    objdir ("%{prj.location}/build/bin-obj/" .. outputDir .. "/%{prj.name}")

	files {
        "%{prj.location}/src/glew.c"
    }

    includedirs {
        "%{prj.location}/include"
    }

	filter "system:windows"
        systemversion "latest"
        staticruntime "On"
		defines {
            "GLEW_NO_GLU",
            "_CRT_SECURE_NO_WARNINGS"
		}
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"

    filter "system:macosx"
        toolset "osx_gcc"
        links {
            "-framework OpenGL"
        }
        xcodebuildsettings {
            ["HEADER_SEARCH_PATHS"] = "include/"
        }
