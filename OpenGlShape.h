#pragma once
#include <GL\glew.h>
#include <vector>
#include <glm\glm.hpp>

class OpenGlShape
{
public:
	OpenGlShape(void);
	~OpenGlShape(void);

public:
	void loadData(std::vector<GLfloat> vertexBufferData, std::vector<GLfloat> textureBufferData);
	void loadData(std::vector<GLfloat> vertexBufferData, std::vector<GLfloat> textureBufferData, std::vector<GLushort> elementBufferData);
	void init(const char * vertexShaderFilePath,const char * fragmentShaderFilePath, const char* textureFilename);
	void draw();
	void setMvp(glm::mat4 mvp);
	void cleanup();

private:
	GLuint _loadShaders(const char * vertex_file_path,const char * fragment_file_path);
	void   _loadTexture(const char* textureFilename);

private:
	GLuint _vertexArrayId;
	GLuint _vertexBuffer;
	GLuint _texCoordBuffer;
	GLuint _programId;
	GLuint _textureId;
	GLuint _elementBuffer;

	GLuint _matrixId;
	glm::mat4 _MVP;

	std::vector<GLfloat> _vertexBufferData;
	std::vector<GLfloat> _textureBufferData;
	std::vector<GLushort> _elementBufferData;
};

