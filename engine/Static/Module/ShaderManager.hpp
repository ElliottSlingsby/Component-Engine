#pragma once

#include <GL\glew.h>
#include <string>
#include <unordered_map>
#include <glm\vec3.hpp>

namespace Module{
	class ShaderManager{
		std::string _shaderPath = "../";

		typedef std::unordered_map<std::string, int> GLintMap;
		typedef std::vector<GLchar> CharVector;
		
		GLintMap _shaders;
		GLintMap _programs;

		std::string _loadText(const std::string& filename);
		bool _glErrorCheck(const std::string& message, GLint target, int check, bool program = false);

	public:
		enum ShaderType{
			FRAGMENT = GL_FRAGMENT_SHADER,
			VERTEX = GL_VERTEX_SHADER
		};

		~ShaderManager();

		void setShaderLocation(const std::string& filepath);
		bool loadShader(const std::string& filename, ShaderType type);

		void createProgram(const std::string& name, const std::string& vertexFilename, const std::string& fragmentFilename);
		void useProgram(const std::string& name = "");

		void attribute(const glm::vec3& vector);
	};
}