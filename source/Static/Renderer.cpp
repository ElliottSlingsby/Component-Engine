#include "Renderer.hpp"

#include <fstream>
#include <SDL_messagebox.h>
#include <Static\DebugOutput.hpp>

Renderer::Renderer(){
	_screen = new Module::Window(true);
}

Renderer& Renderer::_instance(){
	static Renderer instance;
	return instance;
}

Module::Window& Renderer::Window(){
	return *_instance()._screen;
}

Module::Console& Renderer::Console(){
	static Module::Console instance;
	return instance;
}

Module::ShaderManager& Renderer::ShaderManager(){
	static Module::ShaderManager instance;
	return instance;
}

Renderer::~Renderer(){
	_running = false;

	delete _screen;
	_screen = 0;

	SDL_GL_DeleteContext(_glcontext);
	_glcontext = 0;
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
	
	Window().initiate();

	return true;
}

bool Renderer::_setupGL(){
	// OpenGl context object
	_glcontext = SDL_GL_CreateContext(Window().window());

	if (!_glcontext){
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

#ifdef _DEBUG
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 1);
#endif

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

	ShaderManager().initiate();

	return true;
}

bool Renderer::reshape(){
	// Setting up OpenGL matrices
	glViewport(0, 0, Window().width(), Window().height());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ar = (float)Window().width() / (float)Window().height();

	gluPerspective(90 / ar, ar, 0.1, 2048); // 59 vfov = ~90 hfov

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;
}

bool Renderer::initiate(){
	// If already running, reset
	if (_instance()._running){
		
 _instance()._screen;
		_instance()._screen = new Module::Window(true);

		SDL_GL_DeleteContext(_instance()._glcontext);
	}
	else{
		_instance()._running = true;
	}

	// Returns false if failed to setup
	if (!_instance()._setupSDL())
		return false;

	if (!_instance()._setupGL())
		return false;

	return reshape();
}
