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

	AssetLoader::getAsset("teapot.obj");

	while (running){
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT)
				running = false;

			else if (e.type == SDL_KEYDOWN)
				if (e.key.keysym.sym == SDLK_ESCAPE)
					running = false;
		}

		EntityManager::updateAll(0);
		EntityManager::renderAll();
		  
		Window::swapBuffer();
	}

	EntityManager::deleteAll();

	return 0;
}