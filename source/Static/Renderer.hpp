#pragma once

#include "Module\Window.hpp"
#include "Module\ShaderManager.hpp"

class Renderer{
	bool _running = false;

	SDL_GLContext _glcontext = 0;

	Module::Window* _screen = 0;

	bool _setupSDL();
	bool _setupGL(); 
	
	// Private singleton used by static methods
	static Renderer& _instance();

	Renderer();

public:	
	~Renderer();

	static Module::Window& Window();
	static Module::ShaderManager& ShaderManager();
	
	static bool initiate();

	// Reshapes the OpenGL matrices to initial shape
	static bool reshape(); 
};