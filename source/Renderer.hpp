#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <stdio.h>
#include "Vector2.hpp"
#include "Vector3.hpp"
//#include <GL\glut.h> broken?

/*
Note, a Renderer object will be passed around to the render functions of entities and components.

void render(Renderer* renderer)

All rendering can be performed through the renderer object with a nice interface for the programming.

This object should be super efficient with OpenGl / SDL, but also be super friendly and ease to interface with from a component's point of view.
*/

class Renderer{
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_GLContext _glcontext;

	const char* _title;

	Vector2i _size;

public:
	Renderer();
	~Renderer();

	// Setters
	void size(int width, int height);
	void title(const char* title);
	
	// Setup and updating
	bool init();
	void swap();

	// Component methods
	void drawTriangle(Vector3f& v1, Vector3f& v2, Vector3f& v3, Vector3f& colour = Vector3f(1.f, 1.f, 1.f));
};