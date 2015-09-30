#pragma once

#include <GL\glew.h>
#include <string>

namespace Module{
	enum ShaderTypes{
		SHADER_FRAGMENT = GL_FRAGMENT_SHADER,
		SHADER_VERTEX = GL_VERTEX_SHADER,
		SHADER_GEOMATRY = GL_GEOMETRY_SHADER,
	};

	class ShaderManager{
		std::string _shaderPath = "../";

		GLint _shaderProgram = 0;

		GLint _vertexShader = 0;
		GLint _fragmentShader = 0;
		GLint _geomatryShader = 0;

	public:
		~ShaderManager();

		bool initiate();
		//bool compile();
		//bool load();

		void setShaderLocation(const std::string& filepath);
		void loadShader(ShaderTypes type, const std::string& filepath);
		void linkShaders();

		void enableShader(ShaderTypes type, bool enabled);
	};
}