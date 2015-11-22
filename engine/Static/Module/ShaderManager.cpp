#include "ShaderManager.hpp"
#include <Static\DebugOutput.hpp>

#include <fstream>

using namespace Module;

std::string ShaderManager::_loadText(const std::string& filename){
	std::fstream file;

	file.open((_shaderPath + filename).c_str());

	if (!file){
		error_out((std::string("Can't find shader file ") + _shaderPath + filename).c_str());
		return "";
	}

	std::string contents;

	while (!file.eof())	{
		std::string line;
		std::getline(file, line);
		contents += line + "\n";
	}

	file.close();

	return contents;
}

ShaderManager::~ShaderManager(){
	for (GLintMap::iterator i = _shaders.begin(); i != _shaders.end(); i++){
		glDeleteShader(i->second);
	}

	for (GLintMap::iterator i = _programs.begin(); i != _programs.end(); i++){
		glDeleteProgram(i->second);
	}
}

void ShaderManager::setShaderLocation(const std::string& filepath){
	_shaderPath = "../" + filepath + "/";
}

bool ShaderManager::loadShader(const std::string& filename, ShaderType type){
	GLint shader = glCreateShader(type);

	std::string string = _loadText(filename).c_str();
	const char* code = string.c_str();

	glShaderSource(shader, 1, &code, 0);
	glCompileShader(shader);

	if (_glErrorCheck("GL_COMPILE_STATUS", shader, GL_COMPILE_STATUS)){
		glDeleteShader(shader);
		return false;
	}

	_shaders[filename] = shader;
	return true;
}

bool ShaderManager::_glErrorCheck(const std::string& message, GLint target, int check, bool program){
	GLint success;

	if (program)
		glGetProgramiv(target, check, &success);
	else
		glGetShaderiv(target, check, &success);

	if (success == GL_FALSE){
		GLint length = 0;

		if (program)
			glGetProgramiv(target, GL_INFO_LOG_LENGTH, &length);
		else
			glGetShaderiv(target, GL_INFO_LOG_LENGTH, &length);

		CharVector error(length);

		if (program)
			glGetProgramInfoLog(target, length, &length, &error[0]);
		else
			glGetShaderInfoLog(target, length, &length, &error[0]);

		message_out("%s:\n%s\n", message.c_str(), &error[0]);
		
		return true;
	}

	return false;
}

void ShaderManager::createProgram(const std::string& name, const std::string& vertexFilename, const std::string& fragmentFilename){
	GLint program = glCreateProgram();
	
	if (_shaders.find(vertexFilename) == _shaders.end()){
		if (loadShader(vertexFilename, VERTEX) == false){
			glDeleteProgram(program);
			return;
		}
	}

	if (_shaders.find(fragmentFilename) == _shaders.end()){
		if (loadShader(fragmentFilename, FRAGMENT) == false){
			glDeleteProgram(program);
			return;
		}
	}
		
	glAttachShader(program, _shaders[vertexFilename]);

	if (_glErrorCheck("GL_COMPILE_STATUS", program, GL_COMPILE_STATUS, true)){
		glDeleteProgram(program);
		return;
	}

	glAttachShader(program, _shaders[fragmentFilename]);

	if (_glErrorCheck("GL_COMPILE_STATUS", program, GL_COMPILE_STATUS, true)){
		glDeleteProgram(program);
		return;
	}	

	glLinkProgram(program);

	if (_glErrorCheck("GL_LINK_STATUS", program, GL_LINK_STATUS, true)){
		glDeleteProgram(program);
		return;
	}

	glValidateProgram(program);

	if (_glErrorCheck("GL_VALIDATE_STATUS", program, GL_VALIDATE_STATUS, true)){
		glDeleteProgram(program);
		return;
	}

	_programs[name] = program;
}

void ShaderManager::useProgram(const std::string& name){
	if (name != "")
		glUseProgram(_programs[name]);
	else
		glUseProgram(0);
}

void ShaderManager::attribute(const glm::vec3& vector){
	glVertexAttribLPointer(0, 3, GL_FLOAT, sizeof(GL_FLOAT) * 3, &vector.x);
}