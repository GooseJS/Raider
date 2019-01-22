#include "Raider/Application.h"

namespace Raider
{
	Application::Application() : _window(WindowCfg()) {}
	Application::~Application() {}

	void Application::run()
	{
		_window.init(WindowCfg());
		_running = true;

		double currentTime = glfwGetTime();
		double oldTime = glfwGetTime();

		GameSettings::getInstance()->gameTime = new RaiderTime();
		GameSettings::getInstance()->windowData = &_window.getWindowData();

		while (_running)
		{
			GameSettings::getInstance()->gameTime->_currentFrameTime = glfwGetTime();
			GameSettings::getInstance()->gameTime->_deltaTime = GameSettings::getInstance()->gameTime->getCurrentFrameTime() - GameSettings::getInstance()->gameTime->getLastFrameTime();
			GameSettings::getInstance()->gameTime->_lastFrameTime = GameSettings::getInstance()->gameTime->_currentFrameTime;

			_window.update();
			if (_window.shouldClose()) prepareClose();
			update();
			render();
		}

		delete GameSettings::getInstance()->gameTime;
	}
}