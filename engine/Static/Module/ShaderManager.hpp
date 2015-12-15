#pragma once

#include <GL\glew.h>
#include <string>
#include <unordered_map>

#include <glm\vec4.hpp>
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>
#include <glm\mat4x4.hpp>
#include <glm\mat3x3.hpp>
#include <glm\mat2x2.hpp>
#include <glm\mat2x3.hpp>
#include <glm\mat2x4.hpp>
#include <glm\mat3x2.hpp>
#include <glm\mat3x4.hpp>
#include <glm\mat4x2.hpp>
#include <glm\mat4x3.hpp>

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
	bool _glSimpleErrorCheck();
	
	GLint _indexUniform(const std::string& name);
	GLint _indexAttribute(const std::string& name);

public:
	enum ShaderType{
		FRAGMENT = GL_FRAGMENT_SHADER,
		VERTEX = GL_VERTEX_SHADER
	};

	~ShaderManager();

	void enableVertexAttribute(const std::string& name = "position");

	void setShaderLocation(const std::string& filepath);
	bool loadShader(const std::string& filename, ShaderType type);

	void createProgram(const std::string& name, const std::string& vertexFilename, const std::string& fragmentFilename);

	void useProgram(GLuint program);
	void useProgram(const std::string& name = "");

	GLuint currentProgram();

	void uniform(unsigned int index, const glm::mat4& value);
	void uniform(const std::string& name, const glm::mat4& value);
	
	void attribute(unsigned int index, const glm::vec3& value);
	void attribute(const std::string& name, const glm::vec3& value);

	/*

	void uniform(unsigned int index, const glm::mat2& values, unsigned int count = 1){}
	void uniform(unsigned int index, const glm::mat3& values, unsigned int count = 1){}
	void uniform(unsigned int index, const glm::vec4& values, unsigned int count = 1){}
	void uniform(unsigned int index, const glm::vec3& values, unsigned int count = 1){}
	void uniform(unsigned int index, const glm::vec2& values, unsigned int count = 1){}
	void uniform(unsigned int index, float* value, unsigned int count = 1){}
	void uniform(unsigned int index, double* value, unsigned int count = 1){}
	void uniform(unsigned int index, int* value, unsigned int count = 1){}
	void uniform(unsigned int index, unsigned int* value, unsigned int count = 1){}
	void uniform(unsigned int index, bool* value, unsigned int count = 1){}
		
	/*
	
	// Square Matrices
	void attribute(unsigned int index, const glm::mat2& value);
	void attribute(unsigned int index, const glm::mat3& value);
	void attribute(unsigned int index, const glm::mat4& value);

	// NxN Matrices
	void attribute(unsigned int index, const glm::mat2x3& value);
	void attribute(unsigned int index, const glm::mat2x4& value);
	void attribute(unsigned int index, const glm::mat3x2& value);
	void attribute(unsigned int index, const glm::mat3x4& value);
	void attribute(unsigned int index, const glm::mat4x2& value);
	void attribute(unsigned int index, const glm::mat4x3& value);
	
	// Float Vectors
	void attribute(unsigned int index, const glm::vec4& value);
	void attribute(unsigned int index, const glm::vec3& value);
	void attribute(unsigned int index, const glm::vec2& value);

	// Bool Vectors
	void attribute(unsigned int index, const glm::bvec4& value);
	void attribute(unsigned int index, const glm::bvec3& value);
	void attribute(unsigned int index, const glm::bvec2& value);

	// Int Vectors
	void attribute(unsigned int index, const glm::ivec4& value);
	void attribute(unsigned int index, const glm::ivec3& value);
	void attribute(unsigned int index, const glm::ivec2& value);

	// Unsigned Vectors
	void attribute(unsigned int index, const glm::uvec4& value);
	void attribute(unsigned int index, const glm::uvec3& value);
	void attribute(unsigned int index, const glm::uvec2& value);

	// Double Vectors
	void attribute(unsigned int index, const glm::dvec4& value);
	void attribute(unsigned int index, const glm::dvec3& value);
	void attribute(unsigned int index, const glm::dvec2& value);

	// Primitives
	void attribute(unsigned int index, float value);
	void attribute(unsigned int index, double value);
	void attribute(unsigned int index, int value);
	void attribute(unsigned int index, unsigned int value);
	void attribute(unsigned int index, bool value);

	// Primitive Arrays
	void attribute(unsigned int index, const float* value, unsigned int length);
	void attribute(unsigned int index, const double* value, unsigned int length);
	void attribute(unsigned int index, const int* value, unsigned int length);
	void attribute(unsigned int index, const unsigned int* value, unsigned int length);
	void attribute(unsigned int index, const bool* value, unsigned int length);

	// Object Arrays
	void attribute(unsigned int index, const glm::mat2* value, unsigned int length);
	void attribute(unsigned int index, const glm::mat3* value, unsigned int length);
	void attribute(unsigned int index, const glm::mat4* value, unsigned int length);
	void attribute(unsigned int index, const glm::mat2x3* value, unsigned int length);
	void attribute(unsigned int index, const glm::mat2x4* value, unsigned int length);
	void attribute(unsigned int index, const glm::mat3x2* value, unsigned int length);
	void attribute(unsigned int index, const glm::mat3x4* value, unsigned int length);
	void attribute(unsigned int index, const glm::mat4x2* value, unsigned int length);
	void attribute(unsigned int index, const glm::mat4x3* value, unsigned int length);
	void attribute(unsigned int index, const glm::vec4* value, unsigned int length);
	void attribute(unsigned int index, const glm::vec3* value, unsigned int length);
	void attribute(unsigned int index, const glm::vec2* value, unsigned int length);
	void attribute(unsigned int index, const glm::bvec4* value, unsigned int length);
	void attribute(unsigned int index, const glm::bvec3* value, unsigned int length);
	void attribute(unsigned int index, const glm::bvec2* value, unsigned int length);
	void attribute(unsigned int index, const glm::ivec4* value, unsigned int length);
	void attribute(unsigned int index, const glm::ivec3* value, unsigned int length);
	void attribute(unsigned int index, const glm::ivec2* value, unsigned int length);
	void attribute(unsigned int index, const glm::uvec4* value, unsigned int length);
	void attribute(unsigned int index, const glm::uvec3* value, unsigned int length);
	void attribute(unsigned int index, const glm::uvec2* value, unsigned int length);
	void attribute(unsigned int index, const glm::dvec4* value, unsigned int length);
	void attribute(unsigned int index, const glm::dvec3* value, unsigned int length);
	void attribute(unsigned int index, const glm::dvec2* value, unsigned int length);
	*/
};