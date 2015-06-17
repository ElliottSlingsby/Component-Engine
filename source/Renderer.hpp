#pragma once

#define FREEGLUT_LIB_PRAGMAS 0

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <stdio.h>
#include "Vector2.hpp"
#include "Vector3.hpp"
//#include "Mesh.hpp"
//#include "Phong.hpp"
//#include "Sprite.hpp"

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

	// Component drawing methods
	void drawLine(Vector3f& v1, Vector3f& v2, Vector3f& colour = Vector3f(1.f, 1.f, 1.f));
	void drawTriangle(Vector3f& v1, Vector3f& v2, Vector3f& v3, Vector3f& colour = Vector3f(1.f, 1.f, 1.f));
	void drawQuad(Vector3f& v1, Vector3f& v2, Vector3f& v3, Vector3f& v4, Vector3f& colour = Vector3f(1.f, 1.f, 1.f));
	//void drawMesh(Mesh* mesh, Vector3f& position, Phong* phong = 0){}
	//void drawSprite(Sprite* sprite, Vector2f& position){}
};