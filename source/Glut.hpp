#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <stdio.h>
#include <string>

bool init();
void update();
void render();
void close();

SDL_Window* WINDOW = NULL;
SDL_GLContext GLCONTEXT;

void run(){
	bool running = false;

	if (init()){
		running = true;

		while (running){
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0){
				if (e.type == SDL_QUIT){
					running = false;
				}
			}

			update();
			render();
		}
	}
}

bool init(){
	bool success = true;

	Uint32 flags = SDL_INIT_VIDEO;

	const char* title = "My first polygon!";

	int width = 1280;
	int height = 720;

	if (SDL_Init(flags) < 0){
		printf("%s! %s: %s\n", "Failed to initialize SDL", "SDL Error", SDL_GetError());
		success = false;
	}
	else{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		WINDOW = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		if (!WINDOW){
			printf("%s! %s: %s\n", "Failed to create window", "SDL Error", SDL_GetError());
			success = false;
		}
		else{
			GLCONTEXT = SDL_GL_CreateContext(WINDOW);

			if (!GLCONTEXT){
				printf("%s! %s: %s\n", "Failed to create OpenGL context", "SDL Error", SDL_GetError());
				success = false;
			}
			else{
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glClearColor(0.f, 0.f, 0.f, 1.f);
			}
		}
	}

	return success;
}

void update(){
	
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT);

	int width;
	int height;

	SDL_GetWindowSize(WINDOW, &width, &height);

	glTranslatef(width / 2.f, height / 2.f, 0.f);

	glBegin(GL_QUADS);

	glColor3f(0.f, 1.f, 1.f);
	glVertex2f(-50.f, -50.f);
	glVertex2f(50.f, -50.f);
	glVertex2f(50.f, 50.f);
	glVertex2f(-50.f, 50.f);

	glEnd();

	SDL_GL_SwapWindow(WINDOW);
}