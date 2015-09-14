#include "Screen.hpp"
#include <Static\DebugOutput.hpp>
#include <GL\glew.h>

using namespace Module;

Screen::Screen(bool glEnabled){
	_glEnabled = glEnabled;
}

Screen::~Screen(){
	SDL_DestroyWindow(_window);
}

bool Screen::initiate(){
	if (_running){
		SDL_GL_DeleteContext(_glContext);
		_glContext = 0;

		SDL_DestroyRenderer(_renderer);
		_renderer = 0;

		SDL_DestroyWindow(_window);
		_window = 0;
	}

	int flags;

	if (_glEnabled)
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	else
		flags = SDL_WINDOW_SHOWN;

	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, flags);

	if (!_window){
		std::string message = SDL_GetError();

		error_out(message.c_str());
		return false;
	}

	if (_glEnabled){
		_glContext = SDL_GL_CreateContext(_window);

		if (!_glContext){
			std::string message = SDL_GetError();

			error_out(message.c_str());
			return false;
		}
	}

	// Renderer object (for 2D graphics only)
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	
	if (!_renderer){
		std::string message = SDL_GetError();
	
		error_out(message.c_str());
		return false;
	}

	// Set size mode
	SDL_SetWindowFullscreen(_window, _windowMode);

	if (_fixedMouse)
		SDL_SetRelativeMouseMode(SDL_TRUE);

	_running = true;

	return true;
}

void Screen::swapBuffer(){
	SDL_GL_SwapWindow(_window);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::setFixedMouse(bool fixedMouse){
	_fixedMouse = fixedMouse;
}

void Screen::setSize(unsigned int width, unsigned int height){
	_width = width;
	_height = height;

	if (_running){
		SDL_SetWindowSize(_window, width, height);
		initiate();
	}
}

void Screen::setTitle(const char* title){
	_title = title;

	if (_running)
		SDL_SetWindowTitle(_window, title);
}

void Screen::setWindowMode(int windowMode){
	_windowMode = windowMode;

	if (_running)
		SDL_SetWindowFullscreen(_window, windowMode);
}

int Screen::width(){
	return _width;
}

int Screen::height(){
	return _height;
}

SDL_Renderer* Screen::renderer(){
	return _renderer;
}

SDL_GLContext Screen::glContext(){
	return _glContext;
}