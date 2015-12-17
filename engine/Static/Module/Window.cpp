#include "Window.hpp"

#include <Static\DebugOutput.hpp>
#include <GL\glew.h>

Window::~Window(){
	SDL_DestroyWindow(_sdlWindow);
}

bool Window::initiate(){
	close();

	_sdlWindow = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_OPENGL | _windowMode);

	if (!_sdlWindow){
		std::string message = SDL_GetError();

		error_out(message.c_str());
		return false;
	}

	// Set size mode
	SDL_SetWindowFullscreen(_sdlWindow, _windowMode);

	if (_fixedMouse)
		SDL_SetRelativeMouseMode(SDL_TRUE);

	_running = true;
	return true;
}

void Window::close(){
	if (_running){
		SDL_DestroyWindow(_sdlWindow);
		_sdlWindow = 0;
	}
}

bool Window::running(){
	return _running;
}

void Window::flip(){
	SDL_GL_SwapWindow(_sdlWindow);
	glClearColor(0.5f, 0.5f, 0.5f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setFixedMouse(bool fixedMouse){
	_fixedMouse = fixedMouse;
}

void Window::setSize(unsigned int width, unsigned int height){
	_width = width;
	_height = height;

	if (_running){
		SDL_SetWindowSize(_sdlWindow, width, height);
		initiate();
	}
}

void Window::setTitle(const char* title){
	_title = title;

	if (_running)
		SDL_SetWindowTitle(_sdlWindow, title);
}

void Window::setWindowMode(int windowMode){
	_windowMode = windowMode;

	if (_running)
		SDL_SetWindowFullscreen(_sdlWindow, windowMode);
}

void Window::setGlContext(SDL_GLContext glContext){
	SDL_GL_MakeCurrent(_sdlWindow, glContext);
}

int Window::width(){
	return _width;
}

int Window::height(){
	return _height;
}

glm::vec2 Window::size(){
	return glm::vec2(_width, _height);
}

SDL_Window* Window::sdlWindow(){
	return _sdlWindow;
}