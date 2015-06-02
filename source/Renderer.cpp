#include "Renderer.hpp"

Renderer::Renderer(){
	_window = 0;
	_renderer = 0;

	title("My first polygon!");
	size(1280, 720);
}

Renderer::~Renderer(){
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_GL_DeleteContext(_glcontext);
}

void Renderer::size(int width, int height){
	_size = Vector2i(width, height);
}

void Renderer::title(const char* title){
	_title = title;
}

bool Renderer::init(){
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

	// Getting OpenGL context, error handling and setting up OpenGl for first frame
	_glcontext = SDL_GL_CreateContext(_window);

	if (!_glcontext){
		printf("%s! %s: %s\n", "Failed to create OpenGL context", "SDL Error", SDL_GetError());
		return false;
	}

	glMatrixMode(GL_PROJECTION | GL_MODELVIEW | GL_TEXTURE | GL_COLOR);
	glLoadIdentity();

	glClearColor(0.f, 0.f, 0.f, 1.f);

	return true;
}

void Renderer::swap(){
	// Swap and clear buffer
	SDL_GL_SwapWindow(_window);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::renderTest(){
	// Draw multi-colour quad for testing
	glBegin(GL_QUADS);

	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.5f, -0.5f, 0.f);

	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.5f, -0.5f, 0.f);

	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.5f, 0.5f, 0.f);

	glColor3f(1.f, 1.f, 1.f);
	glVertex3f(-0.5f, 0.5f, 0.f);

	glEnd();
}