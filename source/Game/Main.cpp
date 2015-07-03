#include "Window.hpp"
#include "EntityManager.hpp"
#include "Setup.hpp"
#include <time.h>

int main(int argc, char** argv){
	srand((unsigned int)time(0));

	Window::size(1280, 720);
	Window::fullscreen(WINDOW_WINDOWED);
	Window::title("Component Game");
	
	int lastFrame = 0;
	int currFrame = 0;

	bool running = Window::initiate();

	if (running)
		setup();

	while (running){
		lastFrame = currFrame;
		currFrame = SDL_GetTicks();

		SDL_Event e;

		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT)
				running = false;

			else if (e.type == SDL_KEYDOWN)
				if (e.key.keysym.sym == SDLK_ESCAPE)
					running = false;
		}

		float dt = (float)(currFrame - lastFrame) / 1000.f;

		EntityManager::updateAll(dt);
		EntityManager::renderAll();
		  
		Window::swapBuffer();
	}

	EntityManager::deleteAll();

	return 0;
}