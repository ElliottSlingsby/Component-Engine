#pragma once

#include <SDL.h>
#include <GL\glew.h>

#include "Math\Vector2.hpp"

class Window{
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_GLContext _glcontext;

	const char* _title;

	Vector2i _size;

	bool _setupSDL();
	bool _setupGL();
	
	bool _reshape();

public:
	Window();
	~Window();

	// Setters
	void size(int width, int height);
	void title(const char* title);
	
	// Setup and updating
	bool init();
	void swap();
};