#ifndef APP_H
#define APP_H

#include "OpenGlShape.h"
#include "Camera.h"
#include <SFML\Graphics.hpp>

class App
{
public:
	App(void);
	~App(void);

public:
	void run();

private:
	void _update(sf::Time deltaTime);
	void _processEvents();
	void _processInput();
	void _render();
	void _init();
	void _cleanup();

private:
	sf::RenderWindow _window;
	sf::Time	     _fps;
	int		         _keyPressed;

private:
	OpenGlShape _openGlCube;
	OpenGlShape _openGlPlane;
	Camera	    _camera;

private:
	std::vector<GLfloat> _cubeBufferData;
	std::vector<GLfloat> _cubeTextureBufferData;

	std::vector<GLfloat> _planeBufferData;
	std::vector<GLfloat> _planeTextureBufferData;
};

#endif

