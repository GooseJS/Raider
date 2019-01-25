#include "Camera.h"

namespace RaiderCraft
{
	void Camera::generateProjectionMatrix()
	{
		if (Raider::GameSettings::getInstance()->windowData != nullptr)
		{
			_projectionMatrix = glm::perspective(glm::radians(_fov), Raider::GameSettings::getInstance()->windowData->aspectRatio, 0.1f, 1000.0f);
			_rebuildProjectionMatrix = false;
		}
	}

	void Camera::generateMatrices()
	{
		_direction = glm::normalize(glm::vec3(cos(glm::radians(_pitch)) * cos(glm::radians(_yaw)), sin(glm::radians(_pitch)), cos(glm::radians(_pitch)) * sin(glm::radians(_yaw))));
		_right = glm::normalize(glm::cross(_worldUp, _direction));
		_up = glm::normalize(glm::cross(_direction, _right));

		_viewMatrix = glm::lookAt(_position, _position + _direction, _up);
		if (_rebuildProjectionMatrix)
			generateProjectionMatrix();
	}

	void Camera::rotateCamera(float rotX, float rotY)
	{
		_yaw += _mouseSpeed * Raider::GameSettings::getInstance()->gameTime->getDeltaTime() * rotX;
		_pitch += _mouseSpeed * Raider::GameSettings::getInstance()->gameTime->getDeltaTime() * rotY;

		if (_pitch > 89.0f) _pitch = 89.0f;
		else if (_pitch < -89.0f) _pitch = -89.0f;

		if (_yaw > 360.0f) _yaw = 0.f;
		if (_yaw < 0.f) _yaw = 360.0f;
	}

	void Camera::moveCamera(float forwardBack, float strafe, float upDown)
	{
		_position += _direction * Raider::GameSettings::getInstance()->gameTime->getDeltaTime() * forwardBack;
		_position -= _right * Raider::GameSettings::getInstance()->gameTime->getDeltaTime() * strafe;
		_position += _up * Raider::GameSettings::getInstance()->gameTime->getDeltaTime() * upDown;
	}

	void Camera::setCameraPos(float x, float y, float z)
	{
		_position.x = x;
		_position.y = y;
		_position.z = z;
	}
}