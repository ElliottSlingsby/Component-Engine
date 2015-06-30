#pragma once

#include <SDL.h>
#include <GL\glew.h>

#include "Math\Vector2.hpp"

enum WindowModes{
	WINDOW_WINDOWED = SDL_WINDOW_SHOWN,
	WINDOW_FULLSCREEN = SDL_WINDOW_FULLSCREEN,
	WINDOW_FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP
};

class Window{
	bool _running = false;

	SDL_Window* _window = 0;
	SDL_Renderer* _renderer = 0;
	SDL_GLContext _glcontext;

	const char* _title = "My first polygon!";

	Vector2i _size = Vector2i(1280, 720);

	WindowModes _mode = WINDOW_WINDOWED;

	bool _setupSDL();
	bool _setupGL();
	
	static Window& _instance();

public:	
	~Window();

	// Setters
	static void size(int width, int height);
	static Vector2i size();
	static void title(const char* title);
	static void fullscreen(WindowModes mode);

	static int width();
	static int height();
	static SDL_Renderer* renderer();
	
	// Setup and updating
	static bool initiate();
	static void swapBuffer();

	static bool reshape();
};