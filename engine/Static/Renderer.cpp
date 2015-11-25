#include "Renderer.hpp"

#include <fstream>
#include <SDL_messagebox.h>
#include <Static\DebugOutput.hpp>

Renderer::Renderer(){
	_window = new Window();
	_shaderManager = new ShaderManager();
	_console = new Console();
}

Renderer& Renderer::_instance(){
	static Renderer instance;
	return instance;
}

Window& Renderer::window(){
	return *_instance()._window;
}

Console& Renderer::console(){
	return *_instance()._console;
}

ShaderManager& Renderer::shaderManager(){
	return *_instance()._shaderManager;
}

Renderer::~Renderer(){
	_running = false;

	SDL_GL_DeleteContext(_glContext);
	_glContext = 0;

	delete _window;
	delete _shaderManager;
	delete _console;
}

bool Renderer::_setupSDL(){
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
		std::string message = SDL_GetError();

		message_out("%s! %s: %s\n", "Failed to initialize SDL", "SDL Error", message.c_str());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Error", message.c_str(), 0);
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	_window->initiate();

	return true;
}

bool Renderer::_setupGL(){
	// OpenGl context object
	_glContext = SDL_GL_CreateContext(_window->sdlWindow());

	if (!_glContext){
		std::string message = SDL_GetError();
		error_out(message.c_str());
		return false;
	}

	// OpenGl settings
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_FOG);

	 GLenum error = glGetError();

	if (error != GL_NO_ERROR){
		std::string message = reinterpret_cast<const char*>(gluErrorString(error));

		error_out(message.c_str());
		return false;
	}
	
	// Extensions init
	error = glewInit();

	if (error != GLEW_OK){
		std::string message = reinterpret_cast<const char*>(glewGetErrorString(error));

		error_out(message.c_str());
		return false;
	}

	return true;
}

void Renderer::reshape(){
	// Setting up OpenGL matrices
	glViewport(0, 0, window().width(), window().height());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Renderer::initiate(){
	// If already running, reset
	if (_instance()._running){
		_instance()._window->initiate();
		SDL_GL_DeleteContext(_instance()._glContext);

		//_instance()._window = new Window();
		//SDL_GL_DeleteContext(_instance()._glContext);
	}

	// Returns false if failed to setup
	if (!_instance()._setupSDL())
		return false;

	if (!_instance()._setupGL())
		return false;

	_instance()._running = true;

	reshape();

	return true;
}
