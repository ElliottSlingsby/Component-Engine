#include "Window.hpp"
#include "EntityManager.hpp"
#include "Setup.hpp"

int main(int argc, char** argv){
	Window::size(1280, 720);
	Window::fullscreen(WINDOW_WINDOWED);
	Window::title("Component Game");
	
	bool running = Window::initiate();

	if (running)
		setup();

	while (running){
		SDL_Event evnt;
		while (SDL_PollEvent(&evnt) != 0){
			if (evnt.type == SDL_QUIT)
				running = false;

			else if (evnt.type == SDL_KEYDOWN){
				EntityManager::inputAll(evnt);

				if (evnt.key.keysym.sym == SDLK_ESCAPE)
					running = false;
			}
			else if (evnt.type == SDL_KEYUP)
				EntityManager::inputAll(evnt);
		}

		EntityManager::updateAll(0);
		EntityManager::renderAll();
		  
		Window::swapBuffer();
	}

	EntityManager::deleteAll();

	return 0;
}