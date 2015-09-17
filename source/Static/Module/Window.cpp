#include "Window.hpp"

#include <Static\DebugOutput.hpp>
#include <GL\glew.h>
#include "Console.hpp"
#include "SDL_thread.h"

using namespace Module;

static int consoleThread(void* data){
	Window* window = static_cast<Window*>(data);

	Console console;
	console.setPrefix(">>>");

	while (window->running()){
		std::string input = console.getInput();

		int code = console.interpretInput(input);

		if (code == Console::EXIT_CODE)
			window->setRunning(false);
	}

	return 0;
}

Window::Window(bool glEnabled){
	_glEnabled = glEnabled;
}

Window::~Window(){
	SDL_DestroyWindow(_window);
}

bool Window::initiate(){
	if (_running){
		SDL_DestroyRenderer(_renderer);
		_renderer = 0;

		SDL_DestroyWindow(_window);
		_window = 0;
	}

	int flags;

	if (_glEnabled)
		flags = SDL_WINDOW_OPENGL | _windowMode;
	else
		flags = _windowMode;

	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, flags);

	if (!_window){
		std::string message = SDL_GetError();

		error_out(message.c_str());
		return false;
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

bool Window::running(){
	return _running;
}

void Window::swapBuffer(){
	SDL_GL_SwapWindow(_window);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setRunning(bool running){
	_running = running;
}

void Window::setFixedMouse(bool fixedMouse){
	_fixedMouse = fixedMouse;
}

void Window::setSize(unsigned int width, unsigned int height){
	_width = width;
	_height = height;

	if (_running){
		SDL_SetWindowSize(_window, width, height);
		initiate();
	}
}

void Window::setTitle(const char* title){
	_title = title;

	if (_running)
		SDL_SetWindowTitle(_window, title);
}

void Window::setWindowMode(int windowMode){
	_windowMode = windowMode;

	if (_running)
		SDL_SetWindowFullscreen(_window, windowMode);
}

void Window::setGlContext(SDL_GLContext glContext){
	SDL_GL_MakeCurrent(_window, glContext);
}

void Window::startConsole(){
	SDL_CreateThread(consoleThread, "console", this);
}

int Window::width(){
	return _width;
}

int Window::height(){
	return _height;
}

SDL_Renderer* Window::renderer(){
	return _renderer;
}

SDL_Window* Window::window(){
	return _window;
}