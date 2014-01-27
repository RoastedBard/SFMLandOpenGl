#include "App.h"
#include <Windows.h>
#include <iostream>

App::App(void)
	:_window(sf::VideoMode(1024, 768), "SFML Template Project")
{

}

App::~App(void)
{

}

void App::_init()
{
	_window.setVerticalSyncEnabled(true);
	_fps = sf::seconds(1.f / 60.f);
	_camera.setScreenDimension(1024, 768);

	_window.setMouseCursorVisible(false);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) 
	{
		std::cout<<"Failed to initialize GLEW\n";
		return;
	}

	//CUBE
	GLfloat _cubeVertexBufferData[] = 
	{
	//face 1
	-1.0f, -1.0f, 1.0f,
	-1.0f,  1.0f, 1.0f,
	 1.0f,  1.0f, 1.0f,
	 1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	//face 2
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,

	//face 3
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,

	//face 4
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,

	//face 5
	-1.0f, 1.0f,  1.0f,
	-1.0f, 1.0f, -1.0f,
	 1.0f, 1.0f, -1.0f,
	 1.0f, 1.0f, -1.0f,
	 1.0f, 1.0f,  1.0f,
	-1.0f, 1.0f,  1.0f,

	//face 6
	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f
	};

	_cubeBufferData.assign(_cubeVertexBufferData, _cubeVertexBufferData + sizeof(_cubeVertexBufferData) / sizeof(_cubeVertexBufferData[0]));

	GLfloat _cubeTextureCoords[] =
	{
	    0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	};

	_cubeTextureBufferData.assign(_cubeTextureCoords, _cubeTextureCoords + sizeof(_cubeTextureCoords) / sizeof(_cubeTextureCoords[0]));

	_openGlCube.loadData(_cubeBufferData, _cubeTextureBufferData);

	_openGlCube.init("vertex.txt", "fragment.txt", "texture.jpg");

	//PLANE
	/*GLfloat _planeVertexBufferData[] = 
	{
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	};

	_planeBufferData.assign(_planeVertexBufferData, _planeVertexBufferData + sizeof(_planeVertexBufferData) / sizeof(_planeVertexBufferData[0]));

	GLfloat _planeTextureCoords[] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
	};

	_planeTextureBufferData.assign(_planeTextureCoords, _planeTextureCoords + sizeof(_planeTextureCoords) / sizeof(_planeTextureCoords[0]));

	_openGlPlane.loadData(_planeBufferData, _planeTextureBufferData);

	_openGlPlane.init("vertex.txt", "fragment.txt", "texture.jpg");*/

	glClearColor(3/255.f, 144/255.f, 255, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void App::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	_init();

	while(_window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		
		while(timeSinceLastUpdate > _fps)
		{
			timeSinceLastUpdate -= _fps;

			_processEvents();
			
			_processInput();

			_update(_fps);
		}
		
		_render();
	}

	_cleanup();
}

void App::_processEvents()
{
	sf::Event windowEvent;

	while(_window.pollEvent(windowEvent))
	{
		switch(windowEvent.type)
		{
		case sf::Event::KeyPressed:
			if(windowEvent.key.code == sf::Keyboard::Escape)
				_window.close();
		break;

		case sf::Event::KeyReleased:
             if(windowEvent.key.code == sf::Keyboard::W ||
                windowEvent.key.code == sf::Keyboard::A ||
                windowEvent.key.code == sf::Keyboard::S ||
                windowEvent.key.code == sf::Keyboard::D)
                _keyPressed = Key::KEY_RELEASED;
        break;

		case sf::Event::Closed: 
			_window.close();
		break;

		case sf::Event::Resized:
			glViewport(0, 0, windowEvent.size.width, windowEvent.size.height);
		break;
		}
	}
}

void App::_processInput()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
		_keyPressed = Key::KEY_PRESSED_UP;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
		_keyPressed = Key::KEY_PRESSED_DOWN;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
		_keyPressed = Key::KEY_PRESSED_LEFT;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
		_keyPressed = Key::KEY_PRESSED_RIGHT;
    }
}

void App::_update(sf::Time deltaTime)
{
	_camera.computeMatrices(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y, deltaTime.asSeconds(), _keyPressed);

	glm::mat4 ViewMatrix = _camera.getViewMatrix();
	glm::mat4 ProjectionMatrix = _camera.getProjectionMatrix();
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	sf::Vector2i windowCenter(1024/2, 768/2);
	sf::Mouse::setPosition(windowCenter, _window);

	//_openGlPlane.setMvp(MVP);
	_openGlCube.setMvp(MVP);
}

void App::_render()
{
	//_openGlPlane.draw();
	_openGlCube.draw();
	_window.display();
}

void App::_cleanup()
{
	_openGlCube.cleanup();
}