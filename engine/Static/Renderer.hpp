#pragma once

#include "Module\Window.hpp"
#include "Module\ShaderManager.hpp"
#include "Module\Console.hpp"

class Renderer{
	bool _running = false;

	SDL_GLContext _glContext = 0;

	Window* _window = 0;

	bool _setupSDL();
	bool _setupGL(); 
	
	// Private singleton used by static methods
	static Renderer& _instance();

	Renderer();

public:	
	~Renderer();

	static Window& window();
	static ShaderManager& shaderManager();
	static Console& console();
	
	static bool initiate();

	// Reshapes the OpenGL matrices to initial shape
	static void reshape(); 
};