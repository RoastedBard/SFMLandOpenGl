#pragma once
#include <glm\glm.hpp>
#include "Enumerations.h"

class Camera
{
public:
	Camera(void);
	Camera(int screenWidth, int screenHeight);
	~Camera(void);

public:
	void setScreenDimension(int width, int height);
	void computeMatrices(int mouseXpos, int mouseYpos, float deltaTime, int keyPressed);
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();

private:
	glm::vec3 _position;
	glm::vec3 _direction;
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	float	  _horizontalAngle;
	float	  _verticalAngle;
	float	  _initialFoV;
	float	  _speed;
	float	  _mouseSpeed;
	int _screenWidth;
	int _screenHeight;
};

