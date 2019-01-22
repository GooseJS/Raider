#pragma once

#include "Raider/GL.h"
#include "Raider/Core.h"
#include "Raider/event/IEvent.h"

namespace Raider
{
	struct EventWindowOpen : public IEvent
	{
	private:
		WindowData& _windowData;
	public:
		EventWindowOpen(WindowData& windowData) : _windowData(windowData) {}
		WindowData& windowData() { return _windowData; }
	};

	struct EventWindowResize : public IEvent
	{
	private:
		WindowData& _windowData;
	public:
		EventWindowResize(WindowData& windowData) : _windowData(windowData) {}
		WindowData& windowData() { return _windowData; }
	};

	struct EventWindowClose : public IEvent
	{
	private:
		WindowData& _windowData;
	public:
		EventWindowClose(WindowData& windowData) : _windowData(windowData) {}
		WindowData& windowData() { return _windowData; }
	};
}
