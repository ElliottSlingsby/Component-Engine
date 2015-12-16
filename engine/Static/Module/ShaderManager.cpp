#include "ShaderManager.hpp"
#include <Static\DebugOutput.hpp>

#include <fstream>

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

bool ShaderManager::_glErrorCheck(const std::string& message, GLuint target, GLenum error, bool program){
	GLint success;

	if (program)
		glGetProgramiv(target, error, &success);
	else
		glGetShaderiv(target, error, &success);

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

		error_out(("Shader Compile Error " + message + "\n" + &error[0] + "\n").c_str());
		
		return true;
	}

	return false;
}

bool ShaderManager::_glSimpleErrorCheck(){
	GLenum err = glGetError();

	if (err != GL_NO_ERROR){
		message_out("%s: %s\n", "- OpenGL Error", gluErrorString(err));
		return true;
	}

	return false;
}

void ShaderManager::createProgram(const std::string& name, const std::string& vertexFilename, const std::string& fragmentFilename){
	if (_programs[name]){
		message_out("Shader Manager: '%s, %s, %s' already loaded!\n", name.c_str(), vertexFilename.c_str(), vertexFilename.c_str());
		return;
	}

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

	//_glSimpleErrorCheck();

	if (_glErrorCheck("GL_COMPILE_STATUS", program, GL_COMPILE_STATUS, true)){
		glDeleteProgram(program);
		return;
	}

	//_glSimpleErrorCheck();

	glAttachShader(program, _shaders[fragmentFilename]);

	//_glSimpleErrorCheck();

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

void ShaderManager::enableVertexAttribute(const std::string& name){
	glEnableVertexAttribArray(_indexAttribute(name));
}

void ShaderManager::useProgram(GLuint program){
	glUseProgram(program);
	_activeProgram = program;
}

void ShaderManager::useProgram(const std::string& name){
	if (name != "")
		useProgram(_programs[name]);
	else
		useProgram(0);
}

GLuint ShaderManager::currentProgram(){
	return _activeProgram;
}

GLint ShaderManager::_indexUniform(const std::string& name){
	GLint value = glGetUniformLocation(_activeProgram, name.c_str());

	if (value == -1){
		message_out(("Uniform " + name + " == -1.\n").c_str());
	}

	return value;
}

GLint ShaderManager::_indexAttribute(const std::string& name){
	GLint value = glGetAttribLocation(_activeProgram, name.c_str());

	if (value == -1){
		message_out(("Attribute " + name + " == -1.\n").c_str());
	}

	return value;
}

void ShaderManager::uniform(unsigned int index, const glm::mat4& value){
	glUniformMatrix4fv(index, 1, true, &value[0][0]);
}

void ShaderManager::uniform(const std::string& name, const glm::mat4& value){
	uniform(_indexUniform(name), value);
}

void ShaderManager::uniform(unsigned int index, const glm::vec3& value){
	glUniform3fv(index, 1, &value[0]);
}

void ShaderManager::uniform(const std::string& name, const glm::vec3& value){
	uniform(_indexUniform(name), value);
}


void ShaderManager::uniform(unsigned int index, GLint value){
	glUniform1i(index, value);
}



void ShaderManager::uniform(const std::string& name, GLint value){
	uniform(_indexUniform(name), value);
}

void ShaderManager::attribute(unsigned int index, const glm::vec3& value){
	glVertexAttrib3fv(index, &value.x);
}

void ShaderManager::attribute(const std::string& name, const glm::vec3& value){
	attribute(_indexAttribute(name), value);
}

void ShaderManager::attribute(unsigned int index, float value){
	glVertexAttrib1f(index, value);
}

void ShaderManager::attribute(const std::string& name, float value){
	attribute(_indexAttribute(name), value);
}






/*
// Float Vectors
void ShaderManager::attribute(unsigned int index, const glm::vec4& value){
	glVertexAttribLPointer(index, value.length, GL_FLOAT, sizeof(float), &value);
}

void ShaderManager::attribute(unsigned int index, const glm::vec3& value){
	glVertexAttribLPointer(index, value.length, GL_FLOAT, sizeof(float), &value.x);
}

void ShaderManager::attribute(unsigned int index, const glm::vec2& value){
	glVertexAttribLPointer(index, value.length, GL_FLOAT, sizeof(float), &value.x);
}

// Bool Vectors
void ShaderManager::attribute(unsigned int index, const glm::bvec4& value){
	glVertexAttribLPointer(index, value.length, GL_BOOL, sizeof(bool), &value.x);
}

void ShaderManager::attribute(unsigned int index, const glm::bvec3& value){
	glVertexAttribLPointer(index, value.length, GL_BOOL, sizeof(bool), &value.x);
}

void ShaderManager::attribute(unsigned int index, const glm::bvec2& value){
	glVertexAttribLPointer(index, value.length, GL_BOOL, sizeof(bool), &value.x);
}

// Int Vectors
void ShaderManager::attribute(unsigned int index, const glm::ivec4& value){
	glVertexAttribLPointer(index, value.length, GL_INT, sizeof(int), &value.x);
}

void ShaderManager::attribute(unsigned int index, const glm::ivec3& value){
	glVertexAttribLPointer(index, value.length, GL_INT, sizeof(int), &value.x);
}

void ShaderManager::attribute(unsigned int index, const glm::ivec2& value){
	glVertexAttribLPointer(index, value.length, GL_INT, sizeof(int), &value.x);
}

// Unsigned Vectors
void ShaderManager::attribute(unsigned int index, const glm::uvec4& value){
	glVertexAttribLPointer(index, value.length, GL_UNSIGNED_INT, sizeof(unsigned int), &value.x);
}

void ShaderManager::attribute(unsigned int index, const glm::uvec3& value){
	glVertexAttribLPointer(index, value.length, GL_UNSIGNED_INT, sizeof(unsigned int), &value.x);
}

void ShaderManager::attribute(unsigned int index, const glm::uvec2& value){
	glVertexAttribLPointer(index, value.length, GL_UNSIGNED_INT, sizeof(unsigned int), &value.x);
}

// Double Vectors
void ShaderManager::attribute(unsigned int index, const glm::dvec4& value){
	glVertexAttribLPointer(index, value.length, GL_DOUBLE, sizeof(double), &value.x);
}

void ShaderManager::attribute(unsigned int index, const glm::dvec3& value){
	glVertexAttribLPointer(index, value.length, GL_DOUBLE, sizeof(double), &value.x);
}

void ShaderManager::attribute(unsigned int index, const glm::dvec2& value){
	glVertexAttribLPointer(index, value.length, GL_DOUBLE, sizeof(double), &value.x);
}

// Square Matrices
void ShaderManager::attribute(unsigned int index, const glm::mat4& value){
	glVertexAttribLPointer(index, value.length, GL_FLOAT, sizeof(float), &value[0][0]);
}

void ShaderManager::attribute(unsigned int index, const glm::mat3& value){
	glVertexAttribLPointer(index, value.length, GL_FLOAT, sizeof(float), &value[0][0]);
}

void ShaderManager::attribute(unsigned int index, const glm::mat2& value){
	glVertexAttribLPointer(index, value.length, GL_FLOAT, sizeof(float), &value[0][0]);
}

// 2xN Matrices
void ShaderManager::attribute(unsigned int index, const glm::mat2x3& value){
	glVertexAttribLPointer(index, value.length, GL_FLOAT, sizeof(float), &value[0][0]);
}

void ShaderManager::attribute(unsigned int index, const glm::mat2x4& value){
	glVertexAttribLPointer(index, value.length, GL_FLOAT, sizeof(float), &value[0][0]);
}

// 3xN Matrices
void ShaderManager::attribute(unsigned int index, const glm::mat3x2& value){
	glVertexAttribLPointer(index, value.length, GL_FLOAT, sizeof(float), &value[0][0]);
}

void ShaderManager::attribute(unsigned int index, const glm::mat3x4& value){
	glVertexAttribLPointer(index, value.length, GL_FLOAT, sizeof(float), &value[0][0]);
}

// 4xN Matrices
void ShaderManager::attribute(unsigned int index, const glm::mat4x2& value){
	glVertexAttribLPointer(index, value.length, GL_FLOAT, sizeof(float), &value[0][0]);
}

void ShaderManager::attribute(unsigned int index, const glm::mat4x3& value){
	glVertexAttribLPointer(index, value.length, GL_FLOAT, sizeof(float), &value[0][0]);
}

// Primitives
void ShaderManager::attribute(unsigned int index, float value){
	glVertexAttribLPointer(index, 1, GL_FLOAT, sizeof(float), &value);
}

void ShaderManager::attribute(unsigned int index, double value){
	glVertexAttribLPointer(index, 1, GL_DOUBLE, sizeof(double), &value);
}

void ShaderManager::attribute(unsigned int index, int value){
	glVertexAttribLPointer(index, 1, GL_INT, sizeof(int), &value);
}

void ShaderManager::attribute(unsigned int index, unsigned int value){
	glVertexAttribLPointer(index, 1, GL_UNSIGNED_INT, sizeof(unsigned int), &value);
}

void ShaderManager::attribute(unsigned int index, bool value){
	glVertexAttribLPointer(index, 1, GL_BOOL, sizeof(bool), &value);
}

// Primitive Arrays
void ShaderManager::attribute(unsigned int index, const float* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_FLOAT, sizeof(float), value);
}

void ShaderManager::attribute(unsigned int index, const double* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_DOUBLE, sizeof(double), value);
}

void ShaderManager::attribute(unsigned int index, const int* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_INT, sizeof(int), value);
}

void ShaderManager::attribute(unsigned int index, const unsigned int* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_UNSIGNED_INT, sizeof(unsigned int), value);
}

void ShaderManager::attribute(unsigned int index, const bool* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_BOOL, sizeof(bool), value);
}

// Object Arrays
void ShaderManager::attribute(unsigned int index, const glm::mat2* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_FLOAT, sizeof(float), value);
}

void ShaderManager::attribute(unsigned int index, const glm::mat3* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_FLOAT, sizeof(float), value);
}

void ShaderManager::attribute(unsigned int index, const glm::mat4* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_FLOAT, sizeof(float), value);
}

void ShaderManager::attribute(unsigned int index, const glm::mat2x3* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_FLOAT, sizeof(float), value);
}

void ShaderManager::attribute(unsigned int index, const glm::mat2x4* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_FLOAT, sizeof(float), value);
}

void ShaderManager::attribute(unsigned int index, const glm::mat3x2* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_FLOAT, sizeof(float), value);
}

void ShaderManager::attribute(unsigned int index, const glm::mat3x4* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_FLOAT, sizeof(float), value);
}

void ShaderManager::attribute(unsigned int index, const glm::mat4x2* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_FLOAT, sizeof(float), value);
}

void ShaderManager::attribute(unsigned int index, const glm::mat4x3* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_FLOAT, sizeof(float), value);
}

void ShaderManager::attribute(unsigned int index, const glm::vec4* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_FLOAT, sizeof(float), value);
}

void ShaderManager::attribute(unsigned int index, const glm::vec3* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_FLOAT, sizeof(float), value);
}

void ShaderManager::attribute(unsigned int index, const glm::vec2* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_FLOAT, sizeof(float), value);
}

void ShaderManager::attribute(unsigned int index, const glm::bvec4* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_BOOL, sizeof(bool), value);
}

void ShaderManager::attribute(unsigned int index, const glm::bvec3* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_BOOL, sizeof(bool), value);
}

void ShaderManager::attribute(unsigned int index, const glm::bvec2* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_BOOL, sizeof(bool), value);
}

void ShaderManager::attribute(unsigned int index, const glm::ivec4* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_INT, sizeof(int), value);
}

void ShaderManager::attribute(unsigned int index, const glm::ivec3* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_INT, sizeof(int), value);
}

void ShaderManager::attribute(unsigned int index, const glm::ivec2* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_INT, sizeof(int), value);
}

void ShaderManager::attribute(unsigned int index, const glm::uvec4* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_UNSIGNED_INT, sizeof(unsigned int), value);
}

void ShaderManager::attribute(unsigned int index, const glm::uvec3* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_UNSIGNED_INT, sizeof(unsigned int), value);
}

void ShaderManager::attribute(unsigned int index, const glm::uvec2* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_UNSIGNED_INT, sizeof(unsigned int), value);
}

void ShaderManager::attribute(unsigned int index, const glm::dvec4* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_DOUBLE, sizeof(double), value);
}

void ShaderManager::attribute(unsigned int index, const glm::dvec3* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_DOUBLE, sizeof(double), value);
}

void ShaderManager::attribute(unsigned int index, const glm::dvec2* value, unsigned int length){
	glVertexAttribLPointer(index, length, GL_DOUBLE, sizeof(double), value);
}
*/