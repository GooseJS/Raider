#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Raider/GL.h>
#include <Raider/GameSettings.h>

namespace RaiderCraft
{
	class Camera
	{
	private:
		glm::vec3 _position		= glm::vec3(0.0f);
		glm::vec3 _direction	= glm::vec3(0.0f);
		glm::vec3 _right		= glm::vec3(0.0f);
		glm::vec3 _up			= glm::vec3(0.0f);

		glm::vec3 _worldUp		= glm::vec3(0.0f, 1.0f, 0.0f);

		float _yaw = 0.0f;
		float _pitch = 0.0f;
		float _fov = 60.0f;

		float _mouseSpeed = 2.0f;

		glm::mat4 _projectionMatrix;
		glm::mat4 _viewMatrix;

		bool _rebuildProjectionMatrix = true;

		inline void generateProjectionMatrix()
		{
			float width = Raider::GameSettings::getInstance()->windowData->width;
			float height = Raider::GameSettings::getInstance()->windowData->height;
			_projectionMatrix = glm::perspective(glm::radians(_fov), width / height, 0.1f, 1000.0f);

			_rebuildProjectionMatrix = false;
		}

	public:
		Camera() {}
		~Camera() = default;
		Camera(const Camera& cam) { _projectionMatrix = cam._projectionMatrix; }
		Camera& operator=(const Camera& cam) = default;

		inline void generateMatrices()
		{
			_direction = glm::normalize(glm::vec3(cos(glm::radians(_pitch)) * cos(glm::radians(_yaw)), sin(glm::radians(_pitch)), cos(glm::radians(_pitch)) * sin(glm::radians(_yaw))));
			_right = glm::normalize(glm::cross(_worldUp, _direction));
			_up = glm::normalize(glm::cross(_direction, _right));

			_viewMatrix = glm::lookAt(_position, _position + _direction, _up);
			if (_rebuildProjectionMatrix)
				generateProjectionMatrix();
		}

		inline void rotateCamera(float rotX, float rotY)
		{
			_yaw += _mouseSpeed * Raider::GameSettings::getInstance()->gameTime->getDeltaTime() * rotX;
			_pitch += _mouseSpeed * Raider::GameSettings::getInstance()->gameTime->getDeltaTime() * rotY;

			if (_pitch > 89.0f) _pitch = 89.0f;
			else if (_pitch < -89.0f) _pitch = -89.0f;

			if (_yaw > 360.0f) _yaw = 0.f;
			if (_yaw < 0.f) _yaw = 360.0f;
		}

		inline void moveCamera(float forwardBack, float strafe, float upDown)
		{
			_position += _direction * Raider::GameSettings::getInstance()->gameTime->getDeltaTime() * forwardBack;
			_position -= _right * Raider::GameSettings::getInstance()->gameTime->getDeltaTime() * strafe;
			_position += _up * Raider::GameSettings::getInstance()->gameTime->getDeltaTime() * upDown;
		}

		inline void setCameraPos(float x, float y, float z)
		{
			_position.x = x;
			_position.y = y;
			_position.z = z;
		}

		inline glm::mat4 getProjectionMatrix() { return _projectionMatrix; }
		inline glm::mat4 getViewMatrix() { return _viewMatrix; }

		inline glm::vec3 getPosition() { return _position;  }
	};
}