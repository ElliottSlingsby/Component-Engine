#include "ShaderManager.hpp"

#include <fstream>

using namespace Module;

ShaderManager::~ShaderManager(){
	glDetachShader(_shaderProgram, _fragmentShader);
	glDetachShader(_shaderProgram, _vertexShader);
	//glDetachShader(_shaderProgram, _geomatryShader);

	glDeleteShader(_fragmentShader);
	glDeleteShader(_vertexShader);
	//glDeleteShader(_geomatryShader);

	glDeleteProgram(_shaderProgram);
}

bool ShaderManager::initiate(){
	/*
	// Sketchy shader setup
	_shaderProgram = glCreateProgram();

	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glAttachShader(_shaderProgram, _fragmentShader);

	if (error != GL_NO_ERROR){
	std::string message = reinterpret_cast<const char*>(gluErrorString(error));

	message_out("%s! %s: %s\n", "Failed to set initiate shader program", "OpenGL Error", message.c_str());
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Error", message.c_str(), _window);
	return false;
	}
	*/

	return true;
}

void ShaderManager::setShaderLocation(const std::string& filepath){
	_shaderPath = "../" + filepath + "/";
}

void ShaderManager::loadShader(ShaderTypes type, const std::string& filepath){
	std::fstream file;

	file.open((_shaderPath + filepath).c_str());

	if (!file){

		return;
	}

	std::string contents;

	while (!file.eof())	{
		std::string line;
		std::getline(file, line);
		contents += line + "\n";
	}

	file.close();

	const GLchar* code = reinterpret_cast<const GLchar*>(contents.c_str());

	GLint shader = 0;

	if (type == SHADER_FRAGMENT)
		shader = _fragmentShader;
	else if (type == SHADER_VERTEX)
		shader = _vertexShader;
	else
		return;

	glShaderSource(shader, 1, &code, 0);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (success != GL_TRUE){

	}
}

void ShaderManager::linkShaders(){
	glUseProgram(_shaderProgram);

	glLinkProgram(_shaderProgram);

	GLint success;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);

	if (success != GL_TRUE){

	}
}