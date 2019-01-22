#pragma once

#ifdef RD_PLATFORM_WINDOWS
#ifdef RD_BUILD_DLL
#define RAIDER_API __declspec(dllexport)
#else
#define RAIDER_API __declspec(dllimport)
#endif
#else
#define RAIDER_API
#endif

#ifdef RD_ENABLE_ASSERTS
#ifdef RD_PLATFORM_WINDOWS
#define RD_ASSERT(x, ...) { if(!(x)) { RD_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define RD_CORE_ASSERT(x, ...) { if(!(x)) { RD_CORE_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define RD_ASSERT(x, ...) { if (!(x)) { RD_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); assert(x); } }
#define RD_CORE_ASSERT(x, ...) { if(!(x)) { RD_CORE_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); assert(x); } }
#endif
#else
#define RD_ASSERT(x, ...)
#define RD_CORE_ASSERT(x, ...)
#endif

#define RD_STATIC_GET_INSTANCE(x) static RAIDER_API x *getInstance() { static x instance; return &instance; }
#define RD_GET_WINDOW_DATA(x) *(WindowData*)glfwGetWindowUserPointer(x)

namespace Raider
{
	struct WindowData
	{
		const char* title;
		unsigned int width, height;
		bool vSync;

		float oldMouseX;
		float oldMouseY;
	};
}