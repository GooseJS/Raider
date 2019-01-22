#include "Window.h"

namespace Raider
{
	static bool s_glfwInit = false;

	static void glfwError(int id, const char* description)
	{
		RD_CORE_ERROR("OpenGL Error: {}", description);
	}

	Window::Window(const WindowCfg& cfg)
	{
		// TODO: Figure out what the fuck I am doing with this constructor
	}

	void Window::init(const WindowCfg& cfg)
	{
		_data.title = cfg.title;
		_data.width = cfg.width;
		_data.height = cfg.height;

		RD_CORE_INFO("Creating window - {}, {}, {}", _data.title, _data.width, _data.height);

		glfwSetErrorCallback(&glfwError);
		if (!s_glfwInit)
		{
			// TODO: glfwTerminate() on program shutdown
			int status = glfwInit();
			RD_CORE_ASSERT(status, "Could not initialize GLFW.");
			RD_CORE_INFO("Initialized GLFW.");

			s_glfwInit = true;
		}

		_window = glfwCreateWindow((int)_data.width, (int)_data.height, _data.title, nullptr, nullptr);
		glfwMakeContextCurrent(_window);
		glfwSetWindowUserPointer(_window, &_data);
		setVSync(true);

		glewExperimental = true;
		GLenum glewError = glewInit();
		RD_CORE_ASSERT(glewError != GLEW_OK, "Could not initialize GLEW."); // TODO: More error checking for this and for the Window creation

		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = RD_GET_WINDOW_DATA(window);
			data.width = static_cast<unsigned int>(width);
			data.height = static_cast<unsigned int>(height);

			EventWindowResize event(data);
			EventSystem::getInstance()->dispatchEvent<EventWindowResize>(event);
		});

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window)
		{
			WindowData& data = RD_GET_WINDOW_DATA(window);
			EventWindowClose event(data);
			EventSystem::getInstance()->dispatchEvent<EventWindowClose>(event);
		});

		glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			switch (action)
			{
				case GLFW_PRESS:
				{
					EventKeyPressed event(key, scancode, mods);
					EventSystem::getInstance()->dispatchEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					EventKeyReleased event(key, scancode, mods);
					EventSystem::getInstance()->dispatchEvent(event);
					break;
				}
				case GLFW_REPEAT:
				{
					EventKeyRepeat event(key, scancode, mods);
					EventSystem::getInstance()->dispatchEvent(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			switch (action)
			{
				case GLFW_PRESS:
				{
					double xpos, ypos;
					glfwGetCursorPos(window, &xpos, &ypos);
					EventMouseButtonPressed event(button, xpos, ypos);
					EventSystem::getInstance()->dispatchEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					double xpos, ypos;
					glfwGetCursorPos(window, &xpos, &ypos);
					EventMouseButtonPressed event(button, xpos, ypos);
					EventSystem::getInstance()->dispatchEvent(event);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			EventMouseMove event((float)xPos, (float)-yPos, (float)xPos - data.oldMouseX, data.oldMouseY - (float)yPos);
			EventSystem::getInstance()->dispatchEvent(event);

			data.oldMouseX = (float)xPos;
			data.oldMouseY = (float)yPos;
		});

		EventWindowOpen event(_data);
		EventSystem::getInstance()->dispatchEvent<EventWindowOpen>(event);
	}

	void Window::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(_window);
	}

	void Window::setVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		_data.vSync = enabled;
	}

	bool Window::isVSync()
	{
		return _data.vSync;
	}

	bool Window::shouldClose()
	{
		return glfwWindowShouldClose(_window) == GLFW_TRUE;
	}
}