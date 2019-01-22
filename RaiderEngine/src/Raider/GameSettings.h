#pragma once

#include "Raider/Core.h"
#include "Raider/RaiderTime.h"

namespace Raider
{
	struct GameTime
	{
		float deltaTime;
	};

	class GameSettings
	{
	private:
		GameSettings() {};
		~GameSettings() = default;
		GameSettings(const GameSettings& gs) {}
		GameSettings& operator=(const GameSettings& gs) = delete;

	public:
		RD_STATIC_GET_INSTANCE(GameSettings)

		RaiderTime*	gameTime;
		WindowData* windowData;
	};
}