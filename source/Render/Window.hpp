#pragma once

#define FREEGLUT_LIB_PRAGMAS 0

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\freeglut.h>

#include "Math\Vector2.hpp"

class Window{
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_GLContext _glcontext;

	const char* _title;

	Vector2i _size;

	bool _SetupSDL();
	bool _SetupGL();
	
	void _reshape();

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