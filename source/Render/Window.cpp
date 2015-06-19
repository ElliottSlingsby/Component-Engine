#include "Window.hpp"

#include <stdio.h>
#include <gl\GLU.h>

Window::Window(){
	_window = 0;
	_renderer = 0;

	title("My first polygon!");
	size(1280, 720);
}

Window::~Window(){
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_GL_DeleteContext(_glcontext);
}

void Window::size(int width, int height){
	_size = Vector2i(width, height);
}

void Window::title(const char* title){
	_title = title;
}

bool Window::_SetupSDL(){
	// SDL initiation and error catching
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("%s! %s: %s\n", "Failed to initialize SDL", "SDL Error", SDL_GetError());
		return false;
	}

	// Setting OpenGL to 2.1 fixed pipeline
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Creating the window and error handling
	_window = SDL_CreateWindow(_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _size.x(), _size.y(), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!_window){
		printf("%s! %s: %s\n", "Failed to create window", "SDL Error", SDL_GetError());
		return false;
	}

	// Creating the renderer and error handling
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if (!_renderer){
		printf("%s! %s: %s\n", "Failed to create ", "SDL Error", SDL_GetError());
		return false;
	}

	return true;
}

bool Window::_SetupGL(){
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	int argc = 0;
	char** argv = 0;

	glutInit(&argc, argv);

	// Getting OpenGL context and error handling
	_glcontext = SDL_GL_CreateContext(_window);

	if (!_glcontext){
		printf("%s! %s: %s\n", "Failed to create OpenGL context", "SDL Error", SDL_GetError());
		return false;
	}
	
	return true;
}

void Window::_reshape(){
	float ar = (float)_size.x() / (float)_size.y();

	glMatrixMode(GL_VIEWPORT);
	glLoadIdentity();

	glViewport(0, 0, _size.x(), _size.y());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90, ar, 0, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool Window::init(){
	if (!_SetupSDL())
		return false;

	if (!_SetupGL())
		return false;

	_reshape();

	return true;
}

void Window::swap(){
	// Swap and clear buffer
	SDL_GL_SwapWindow(_window);
	glClear(GL_COLOR_BUFFER_BIT);
}