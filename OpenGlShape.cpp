#include "OpenGlShape.h"
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

OpenGlShape::OpenGlShape(void)
{
}


OpenGlShape::~OpenGlShape(void)
{
}

void OpenGlShape::setMvp(glm::mat4 mvp)
{
	_MVP = mvp;
}

void OpenGlShape::loadData(std::vector<GLfloat> vertexBufferData, std::vector<GLfloat> textureBufferData)
{
	_vertexBufferData = vertexBufferData;
	_textureBufferData = textureBufferData;
}

void OpenGlShape::loadData(std::vector<GLfloat> vertexBufferData, std::vector<GLfloat> textureBufferData, std::vector<GLushort> elementBufferData)
{
	_vertexBufferData = vertexBufferData;
	_textureBufferData = textureBufferData;
	_elementBufferData = elementBufferData;
}

void OpenGlShape::init(const char * vertexShaderFilePath, const char * fragmentShaderFilePath, const char* textureFilename)
{
	glGenVertexArrays(1, &_vertexArrayId);
	glBindVertexArray(_vertexArrayId);

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _vertexBufferData.size() * sizeof(GLfloat), &_vertexBufferData.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &_texCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, _textureBufferData.size() * sizeof(GLfloat), &_textureBufferData.front(), GL_STATIC_DRAW);

	_programId = _loadShaders(vertexShaderFilePath, fragmentShaderFilePath);
	
	_matrixId = glGetUniformLocation(_programId, "MVP");

	_loadTexture(textureFilename);
}

void OpenGlShape::_loadTexture(const char* textureFilename)
{
	sf::Image image;
	if(!image.loadFromFile(textureFilename))
	{
		std::cout<<"Failed to load texture from file\n";
		return;
	}

	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glActiveTexture(GL_TEXTURE0);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGBA, image.getSize().x, image.getSize().y);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
 //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
}

void OpenGlShape::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(_programId);

	glUniformMatrix4fv(_matrixId, 1, GL_FALSE, &_MVP[0][0]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, _texCoordBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer
	(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, _vertexBufferData.size() / 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

GLuint OpenGlShape::_loadShaders(const char * vertex_file_path,const char * fragment_file_path)
{
	// Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

    // Link the program
    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage( std::max(InfoLogLength, int(1)) );
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

void OpenGlShape::cleanup()
{
	glDeleteVertexArrays(1, &_vertexArrayId);
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_texCoordBuffer);
	glDeleteTextures(1, &_textureId);
	glDeleteProgram(_programId);
}
