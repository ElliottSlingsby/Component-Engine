#include "Window.hpp"

#include <stdio.h>

Window::Window(){
	// Defualt values
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

bool Window::_setupSDL(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("%s! %s: %s\n", "Failed to initialize SDL", "SDL Error", SDL_GetError());
		return false;
	}

	// Setting OpenGL to 2.1 fixed pipeline
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Window object
	_window = SDL_CreateWindow(_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _size.x(), _size.y(), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!_window){
		printf("%s! %s: %s\n", "Failed to create window", "SDL Error", SDL_GetError());
		return false;
	}

	// Renderer object (for 2D graphics only)
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if (!_renderer){
		printf("%s! %s: %s\n", "Failed to create ", "SDL Error", SDL_GetError());
		return false;
	}

	return true;
}

bool Window::_setupGL(){
	// OpenGl settings
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glShadeModel(GL_FLAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// OpenGl context object
	_glcontext = SDL_GL_CreateContext(_window);

	if (!_glcontext){
		printf("%s! %s: %s\n", "Failed to create OpenGL context", "SDL Error", SDL_GetError());
		return false;
	}

	// Extensions
	GLenum error = glewInit();

	if (error != GLEW_OK){
		printf("%s! %s: %s\n", "Failed to initiate Glew", "Glew Error", glewGetErrorString(error));
		return false;
	}

	return true;
}

bool Window::_reshape(){
	// Setting up OpenGL matrices
	float ar = (float)_size.x() / (float)_size.y();

	glViewport(0, 0, _size.x(), _size.y());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 59 vfov = ~90 hfov
	gluPerspective(59, ar, 0, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLenum error = glGetError();

	if (error != GL_NO_ERROR){
		printf("%s! %s: %s\n", "Failed to reshape OpenGL matrices", "OpenGL Error", gluErrorString(error));
		return false;
	}

	return true;
}

bool Window::init(){
	if (!_setupSDL())
		return false;

	if (!_setupGL())
		return false;

	return _reshape();
}

void Window::swap(){
	// Swap and clear
	SDL_GL_SwapWindow(_window);
	glClear(GL_COLOR_BUFFER_BIT);
}