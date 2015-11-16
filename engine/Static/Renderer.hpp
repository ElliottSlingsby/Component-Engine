#pragma once

#include "Module\Window.hpp"
#include "Module\ShaderManager.hpp"
#include "Module\Console.hpp"

class Renderer{
	bool _running = false;

	SDL_GLContext _glContext = 0;

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
	static Module::Console& Console();
	
	static bool initiate();

	// Reshapes the OpenGL matrices to initial shape
	static bool reshape(); 
};