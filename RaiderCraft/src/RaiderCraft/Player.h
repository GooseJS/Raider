#pragma once

#include "render/Camera.h"

namespace RaiderCraft
{
	struct PlayerMovement
	{
		bool moveForwardPressed;
		bool moveBackPressed;
		bool moveLeftPressed;
		bool moveRightPressed;
		bool moveUpPressed;
		bool moveDownPressed;
	};

	class Player
	{
	private:
		float _x;
		float _y;
		float _z;

		float _moveSpeed;

		Camera _playerCamera;
	public:
		Player()
		{
			_x = 0.0f;
			_y = 0.0f;
			_z = 0.0f;
			_moveSpeed = 10.0f;
		}

		void handleMovementInput(const PlayerMovement& movement);
		void handleRotationInput(const float rotX, const float rotY);

		float getX() { return _x; }
		float getY() { return _y; }
		float getZ() { return _z; }

		Camera& getPlayerCamera() { return _playerCamera; }
	};
}