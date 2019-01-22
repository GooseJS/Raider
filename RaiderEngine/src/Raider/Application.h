#pragma once

#include <memory>

#include "Raider/Core.h"
#include "Raider/Logger.h"
#include "Raider/GameSettings.h"
#include "Raider/window/Window.h"

namespace Raider
{
	class RAIDER_API Application
	{
	private:
		bool _running = false;
		Window _window;
	protected:
		virtual void update() {}
		virtual void render() {}

		virtual void prepareClose() { close(); }

		void close() { _running = false; }

		inline Window& getWindow() { return _window;  }
	public:
		Application();
		virtual ~Application();

		void run();
	};

	Application* createApplication();
}