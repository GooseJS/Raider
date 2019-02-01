project "GLFW"
    location "../../lib/glfw"
    kind "StaticLib"
    language "C"

	targetdir ("%{prj.location}/build/bin/" .. outputDir .. "/%{prj.name}")
    objdir ("%{prj.location}/build/bin-obj/" .. outputDir .. "/%{prj.name}")

	files
	{
        "%{prj.location}/src/context.c",
        "%{prj.location}/src/init.c",
        "%{prj.location}/src/input.c",
        "%{prj.location}/src/monitor.c",
        "%{prj.location}/src/vulkan.c",
        "%{prj.location}/src/window.c"
    }

	filter "system:windows"
        buildoptions { "-std=c11", "-lgdi32" }
        systemversion "latest"
        staticruntime "On"

        files {
            "%{prj.location}/src/win32_init.c",
            "%{prj.location}/src/win32_joystick.c",
            "%{prj.location}/src/win32_monitor.c",
            "%{prj.location}/src/win32_time.c",
            "%{prj.location}/src/win32_thread.c",
            "%{prj.location}/src/win32_window.c",
            "%{prj.location}/src/wgl_context.c",
            "%{prj.location}/src/egl_context.c",
            "%{prj.location}/src/osmesa_context.c"
        }

		defines {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
		}
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"

    filter "system:macosx"
        toolset "osx_gcc"
        defines {
            "_GLFW_COCOA",
            "_GLFW_NSGL",
            "_GLFW_USE_OPENGL"
        }
        links {
            "/Library/System/Cocoa.framework",
            "/Library/System/IOKit.framework",
            "/Library/System/CoreFoundation.framework",
            "/Library/System/CoreVideo.framework"
        }
        files {
            "%{prj.location}/src/cocoa_init.m",
            "%{prj.location}/src/cocoa_joystick.m",
            "%{prj.location}/src/cocoa_monitor.m",
            "%{prj.location}/src/cocoa_window.m",
            "%{prj.location}/src/cocoa_time.c",
            "%{prj.location}/src/posix_thread.c",
            "%{prj.location}/src/nsgl_context.m",
            "%{prj.location}/src/egl_context.c",
            "%{prj.location}/src/osmesa_context.c"
        }
