#include "Window.hpp"
#include "EntityManager.hpp"

#include "Prefab\Stub.hpp"

#include "Component\Light.hpp"

int main(int argc, char** argv){

	Window::size(1280, 720);
	Window::fullscreen(WINDOW_WINDOWED);
	Window::title("Component Game");

	Entity* stub = EntityManager::instantiate<Stub>();

	Entity* light = EntityManager::instantiate();

	light->addComponent(new Light);
	
	bool running = Window::initiate();

	EntityManager::loadAll();

	while (running){
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT)
				running = false;
			
			else if(e.type == SDL_KEYDOWN)
				if (e.key.keysym.sym == SDLK_ESCAPE)
					running = false;
		}

		EntityManager::updateAll();
		EntityManager::renderAll();

		Window::swap();
	}

	return 0;
}