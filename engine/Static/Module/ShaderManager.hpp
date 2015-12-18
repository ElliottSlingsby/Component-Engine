#pragma once

#include <GL\glew.h>
#include <string>
#include <unordered_map>

#include <Maths\Vec2.hpp>
#include <Maths\Vec3.hpp>
#include <Maths\Mat4.hpp>

#include <Static\DebugOutput.hpp>

class ShaderManager{
	std::string _shaderPath = "../";

	typedef std::unordered_map<std::string, int> GLintMap;
	typedef std::vector<GLchar> CharVector;
	
	GLintMap _shaders;
	GLintMap _programs;

	GLuint _activeProgram = 0;

	std::string _loadText(const std::string& filename);
	bool _glErrorCheck(const std::string& message, GLuint target, GLenum error, bool program = false);

	GLint _indexUniform(const std::string& name);
	GLint _indexAttribute(const std::string& name);

public:
	enum ShaderType{
		FRAGMENT = GL_FRAGMENT_SHADER,
		VERTEX = GL_VERTEX_SHADER
	};

	~ShaderManager();

	bool _glSimpleErrorCheck(); // TESTING ONLY

	void enableVertexAttribute(const std::string& name = "position");

	void setShaderLocation(const std::string& filepath);
	bool loadShader(const std::string& filename, ShaderType type);

	void createProgram(const std::string& name, const std::string& vertexFilename, const std::string& fragmentFilename);

	void useProgram(GLuint program);
	void useProgram(const std::string& name = "");

	GLuint currentProgram();

	void uniform(unsigned int index, Mat4 value);
	void uniform(const std::string& name, const Mat4& value);

	void uniform(unsigned int index, const Vec3& value);
	void uniform(const std::string& name, const Vec3& value);

	void uniform(unsigned int index, const Vec2& value);
	void uniform(const std::string& name, const Vec2& value);

	void uniform(unsigned int index, GLint value);
	void uniform(const std::string& name, GLint value);

	
	void attribute(unsigned int index, const Vec3& value);
	void attribute(const std::string& name, const Vec3& value);

	void attribute(unsigned int index, float value);
	void attribute(const std::string& name, float value);
};