#include "Static\Renderer.hpp"
#include <SDL.h>
#include <stdio.h>
#include "Static\DebugPrint.hpp"
#include <fstream>
#include <SDL_messagebox.h>

Renderer& Renderer::_instance(){
	static Renderer instance;
	return instance;
}

Renderer::~Renderer(){
	_running = false;

	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_sdlRenderer);
	SDL_GL_DeleteContext(_glcontext);

	/*glDetachShader(_shaderProgram, _fragmentShader);
	glDetachShader(_shaderProgram, _vertexShader);
	//glDetachShader(_shaderProgram, _geomatryShader);

	glDeleteShader(_fragmentShader);
	glDeleteShader(_vertexShader);
	//glDeleteShader(_geomatryShader);

	glDeleteProgram(_shaderProgram);*/
}

bool Renderer::_setupSDL(){
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
		std::string message = SDL_GetError();

		printd("%s! %s: %s\n", "Failed to initialize SDL", "SDL Error", message.c_str());
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

	// Renderer object
	_window = SDL_CreateWindow(_windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _windowSize.x, _windowSize.y, SDL_WINDOW_OPENGL);

	if (!_window){
		std::string message = SDL_GetError();

		printd("%s! %s: %s\n", "Failed to create renderer", "SDL Error", message.c_str());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Error", message.c_str(), 0);
		return false;
	}

	// Renderer object (for 2D graphics only)
	_sdlRenderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if (!_sdlRenderer){
		std::string message = SDL_GetError();

		printd("%s! %s: %s\n", "Failed to create SDL renderer", "SDL Error", message.c_str());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Error", message.c_str(), _window);
		return false;
	}

	// Set size mode
	SDL_SetWindowFullscreen(_window, _windowMode);

	// Lock the mouse
	SDL_SetRelativeMouseMode(SDL_TRUE);

	return true;
}

bool Renderer::_setupGL(){
	// OpenGl context object
	_glcontext = SDL_GL_CreateContext(_window);

	if (!_glcontext){
		std::string message = SDL_GetError();

		printd("%s! %s: %s\n", "Failed to create OpenGL context", "SDL Error", message.c_str());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Error", message.c_str(), _window);
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

	int hpad = 0;
	int vpad = 75;

	glScissor(hpad, vpad, _windowSize.x - hpad * 2, _windowSize.y - vpad * 2);

	float density = 0.f;

	glFogf(GL_FOG_DENSITY, density);

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

		printd("%s! %s: %s\n", "Failed to set OpenGL parameters", "OpenGL Error", message.c_str());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Error", message.c_str(), _window);
		return false;
	}
	
	// Extensions init
	error = glewInit();

	if (error != GLEW_OK){
		std::string message = reinterpret_cast<const char*>(glewGetErrorString(error));

		printd("%s! %s: %s\n", "Failed to initiate Glew", "Glew Error", message.c_str());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Error", message.c_str(), _window);
		return false;
	}

	/*
	// Sketchy shader setup
	_shaderProgram = glCreateProgram();

	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glAttachShader(_shaderProgram, _fragmentShader);

	if (error != GL_NO_ERROR){
		std::string message = reinterpret_cast<const char*>(gluErrorString(error));

		printd("%s! %s: %s\n", "Failed to set initiate shader program", "OpenGL Error", message.c_str());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Error", message.c_str(), _window);
		return false;
	}
	*/

	return true;
}

bool Renderer::reshape(){
	// Setting up OpenGL matrices
	glViewport(0, 0, _instance()._windowSize.x, _instance()._windowSize.y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ar = (float)_instance()._windowSize.x / (float)_instance()._windowSize.y;

	gluPerspective(59, ar, 0.1, 1024 * 2); // 59 vfov = ~90 hfov

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLenum error = glGetError();

	if (error != GL_NO_ERROR){
		std::string message = reinterpret_cast<const char*>(gluErrorString(error));

		printd("%s! %s: %s\n", "Failed to reshape OpenGL matrices", "OpenGL Error", message.c_str());
		return false;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;
}

bool Renderer::initiate(){
	// If already running, reset
	if (_instance()._running){
		SDL_DestroyWindow(_instance()._window);
		SDL_DestroyRenderer(_instance()._sdlRenderer);
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

void Renderer::swapBuffer(){
	// Swap and clean
	SDL_GL_SwapWindow(_instance()._window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

SDL_Renderer* Renderer::sdlRenderer(){
	return _instance()._sdlRenderer;
}

int Renderer::windowWidth(){
	return _instance()._windowSize.x;
}

int Renderer::windowHeight(){
	return _instance()._windowSize.y;
}

void Renderer::setWindowMode(WindowModes mode){
	_instance()._windowMode = mode;
	
	if (_instance()._running)
		SDL_SetWindowFullscreen(_instance()._window, mode);
}

void Renderer::setWindowSize(int width, int height){
	_instance()._windowSize = glm::vec2(width, height);

	if (_instance()._running){
		SDL_SetWindowSize(_instance()._window, width, height);
		_instance().initiate();
	}
}

void Renderer::setWindowTitle(const char* title){
	_instance()._windowTitle = title;

	if (_instance()._running)
		SDL_SetWindowTitle(_instance()._window, title);
}

void Renderer::setShaderLocation(std::string filepath){
	_instance()._shaderPath = "../" + filepath + "/";
}

void Renderer::loadShader(ShaderTypes type, std::string filepath){
	std::fstream file;

	file.open((_instance()._shaderPath + filepath).c_str());

	if (!file){
		printd("Can't find shader '%s'!\n", filepath.c_str());
		return;
	}

	std::string contents;

	while (!file.eof())	{
		std::string line;
		std::getline(file, line);
		contents += line + "\n";
	}

	file.close();

	const GLchar* code = reinterpret_cast<const GLchar*>(contents.c_str());

	GLint shader = 0;

	if (type == SHADER_FRAGMENT)
		shader = _instance()._fragmentShader;
	else if (type == SHADER_VERTEX)
		shader = _instance()._vertexShader;
	else
		return;

	glShaderSource(shader, 1, &code, 0);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (success != GL_TRUE){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Error", "Shader code couldn't compile!", _instance()._window);
	}
}

void Renderer::linkShaders(){
	glUseProgram(_instance()._shaderProgram);

	glLinkProgram(_instance()._shaderProgram);

	GLint success;
	glGetProgramiv(_instance()._shaderProgram, GL_LINK_STATUS, &success);

	if (success != GL_TRUE){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Error", "Shaders couldn't be linked!", _instance()._window);
	}
}
