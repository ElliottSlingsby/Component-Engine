#pragma once

#include <SDL.h>
#include <GL\glew.h>
#include <string>
#include <glm\vec2.hpp>

enum ShaderTypes{
	SHADER_FRAGMENT = GL_FRAGMENT_SHADER,
	SHADER_VERTEX = GL_VERTEX_SHADER,
	SHADER_GEOMATRY = GL_GEOMETRY_SHADER,
};

// Renderer modes, derived from SDL renderer modes
enum WindowModes{
	WINDOW_WINDOWED = SDL_WINDOW_SHOWN,
	WINDOW_FULLSCREEN = SDL_WINDOW_FULLSCREEN,
	WINDOW_FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP
};

class Renderer{
	bool _running = false;

	SDL_Window* _window = 0;
	SDL_Renderer* _sdlRenderer = 0; // Hasn't really been used yet
	SDL_GLContext _glcontext;

	const char* _windowTitle = "3D Component Engine";

	glm::uvec2 _windowSize = glm::uvec2(1280, 720);

	WindowModes _windowMode = WINDOW_WINDOWED;

	std::string _shaderPath = "../";

	GLint _shaderProgram = 0;

	GLint _vertexShader = 0;
	GLint _fragmentShader = 0;
	//GLint _geomatryShader = 0;

	bool _setupSDL(); // Returns false if failed
	bool _setupGL();  // "
	
	// Private singleton used by static methods
	static Renderer& _instance();

public:	
	~Renderer();

	// Setters
	static void setWindowSize(int width, int height);
	static void setWindowTitle(const char* title);
	static void setWindowMode(WindowModes mode);

	// Getters
	static int windowWidth();
	static int windowHeight();
	static SDL_Renderer* sdlRenderer();
	
	// Setup and updating
	static bool initiate();
	static void swapBuffer();

	// Reshapes the OpenGL matrices to initial shape
	static bool reshape(); 

	static void setShaderLocation(std::string filepath);
	static void loadShader(ShaderTypes type, std::string filepath);
	static void linkShaders();

	//static void enableShader(ShaderTypes type, bool enabled);
};