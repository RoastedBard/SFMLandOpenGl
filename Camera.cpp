#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
	_position = glm::vec3(0, 0, 5);
	_horizontalAngle = 3.14f;
	_verticalAngle = 0.0f;
	_initialFoV = 45.0f;
	_speed = 5.0f;
	_mouseSpeed = 0.02f;
}

Camera::Camera(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_position = glm::vec3(0, 0, 5);
	_horizontalAngle = 3.14f;
	_verticalAngle = 0.0f;
	_initialFoV = 45.0f;
	_speed = 3.0f;
	_mouseSpeed = 0.02f;
}


Camera::~Camera(void)
{
}

void Camera::setScreenDimension(int width, int height)
{
	_screenWidth = width;
	_screenHeight = height;
}

void Camera::computeMatrices(int mouseXpos, int mouseYpos, float deltaTime, int keyPressed)
{
	_horizontalAngle += _mouseSpeed * deltaTime * float(_screenWidth / 2 - mouseXpos);
	_verticalAngle += _mouseSpeed * deltaTime * float(_screenHeight / 2 - mouseYpos);

	_direction = glm::vec3
	(
		cos(_verticalAngle) * sin(_horizontalAngle),
		sin(_verticalAngle),
		cos(_verticalAngle) * cos(_horizontalAngle)
	);

	glm::vec3 right = glm::vec3
	(
		sin(_horizontalAngle - 3.14f/2.0f), 
		0,
		cos(_horizontalAngle - 3.14f/2.0f)
	);

	glm::vec3 up = glm::cross( right, _direction );

	switch(keyPressed)
	{
	case Key::KEY_PRESSED_UP:
		_position += _direction * deltaTime * _speed;
		break;

	case Key::KEY_PRESSED_DOWN:
		_position -= _direction * deltaTime * _speed;
		break;

	case Key::KEY_PRESSED_LEFT:
		_position -= right * deltaTime * _speed;
		break;

	case Key::KEY_PRESSED_RIGHT:
		_position += right * deltaTime * _speed;
		break;

	case Key::KEY_RELEASED:
		break;
	}

	_projectionMatrix = glm::perspective(_initialFoV, 4.0f / 3.0f, 0.1f, 100.0f);

	_viewMatrix = glm::lookAt
	(
		_position,           // Camera is here
		_position+_direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return _projectionMatrix;
}

glm::mat4 Camera::getViewMatrix()
{
	return _viewMatrix;
}